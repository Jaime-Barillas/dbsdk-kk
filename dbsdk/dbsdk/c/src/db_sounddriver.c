#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "db_sounddriver.h"
#include "db_audio.h"
#include "db_io.h"
#include "db_log.h"

typedef struct sound_voice
{
    uint32_t slot;
    uint8_t priority;
    uint8_t isPlaying;
    uint32_t id;
    double playTime;
} sound_voice;

typedef struct
{
    // riff chunk desc
    char riff[4];          // RIFF string
    uint32_t overall_size; // overall size of file in bytes
    char wave[4];          // WAVE string
} wavHeader;

typedef struct
{
    // fmt sub-chunk
    char fmt_chunk_marker[4]; // fmt string with trailing null char
    uint32_t length_of_fmt;   // length of the format data
    uint16_t format_type;     // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
    uint16_t channels;        // no.of channels
    uint32_t sample_rate;     // sampling rate (blocks per second)
    uint32_t byterate;        // SampleRate * NumChannels * BitsPerSample/8
    uint16_t block_align;     // In the case of IMA ADPCM, this is size of each block of ADPCM data
    uint16_t bits_per_sample; // bits per sample, 8- 8bits, 16- 16 bits etc
} wavHeaderFmt;

typedef struct
{
    char id[4];
    uint32_t chunk_size;
} wavChunkHeader;

sound_voice _voices[32];
sound_emitter *_ll_emitter_head;
sound_emitter *_ll_voice_tail;

Vec3 _listenerPos;
Quaternion _listenerRot;

void queueStartVoice(uint32_t slot, double time)
{
    _voices[slot].isPlaying = true;
    audio_queueStartVoice(slot, time);
}

void queueStopVoice(uint32_t slot, double time)
{
    _voices[slot].isPlaying = false;
    audio_queueStopVoice(slot, time);
}

// allocate a voice for playback
// attempts to find a voice that isn't already playing - otherwise, interrupt the oldest voice lower than or equal to the given priority
// if a voice could not be allocated (all voices are playing and are higher priority), NULL is returned

int voiceSearchStartIdx = 0;
sound_voice *allocateVoice(uint8_t priority)
{
    sound_voice *voice = NULL;

    // a little silly but:
    // voice stealing scheme can sometimes steal voices too early because we have to schedule playback in advance
    // a simple round-robin search offset helps alleviate this

    for (int i = 0; i < 32; i++)
    {
        int idx = (i + voiceSearchStartIdx) % 32;
        sound_voice *vi = &_voices[idx];

        if (!vi->isPlaying && !audio_getVoiceState(idx))
        {
            voice = vi;
            break;
        }
        else if ((voice == NULL || vi->playTime < voice->playTime) && vi->priority >= priority)
        {
            voice = vi;
        }
    }

    voiceSearchStartIdx++;

    if (voice != NULL)
    {
        voice->priority = priority;
    }
    return voice;
}

// update hardware voice with virtual voice state
void update_voice(sound_emitter *emitter)
{
    if (emitter->voice != NULL && emitter->id == emitter->voice->id)
    {
        double t = audio_getTime();
        sound_voice *voice = emitter->voice;

        float gain = emitter->volume;
        float pan = emitter->pan;

        // apply attenuation + panning relative to listener
        if (emitter->is3D)
        {
            // calculate gain from distance
            float dist = clamp(vec3_distance(emitter->position, _listenerPos), emitter->attenMinDist, emitter->attenMaxDist);
            switch (emitter->attenType)
            {
            case SOUND_ATTEN_INV_DISTANCE:
                gain *= emitter->attenMinDist / (emitter->attenMinDist + emitter->attenRolloff * (dist - emitter->attenMinDist));
                break;
            case SOUND_ATTEN_LINEAR:
                gain *= (1.0f - emitter->attenRolloff * (dist - emitter->attenMinDist) / (emitter->attenMaxDist - emitter->attenMinDist));
                break;
            case SOUND_ATTEN_EXP_DISTANCE:
                gain *= powf(dist / emitter->attenMinDist, -emitter->attenRolloff);
                break;
            }

            // calculate panning
            // transform source position into listener local space
            Vec3 localPos = vec3_sub(emitter->position, _listenerPos);
            Quaternion invRot = _listenerRot;
            quat_invert(&invRot);
            localPos = vec3_transformQuat(invRot, localPos);

            // normalize vector and use .x as pan value
            vec3_normalize(&localPos);
            pan = localPos.x;
        }

        audio_queueSetParam_i(voice->slot, AUDIO_VOICEPARAM_SAMPLEDATA, emitter->sample.handle, t);
        audio_queueSetParam_i(voice->slot, AUDIO_VOICEPARAM_SAMPLERATE, emitter->sample.samplerate, t);
        audio_queueSetParam_i(voice->slot, AUDIO_VOICEPARAM_LOOPENABLE, emitter->loop, t);
        audio_queueSetParam_i(voice->slot, AUDIO_VOICEPARAM_LOOPSTART, 0, t);
        audio_queueSetParam_i(voice->slot, AUDIO_VOICEPARAM_LOOPEND, 0, t);
        audio_queueSetParam_i(voice->slot, AUDIO_VOICEPARAM_RVBENABLE, emitter->reverb, t);
        audio_queueSetParam_f(voice->slot, AUDIO_VOICEPARAM_VOLUME, gain, t);
        audio_queueSetParam_f(voice->slot, AUDIO_VOICEPARAM_PITCH, emitter->pitch, t);
        audio_queueSetParam_f(voice->slot, AUDIO_VOICEPARAM_DETUNE, 0.0f, t);
        audio_queueSetParam_f(voice->slot, AUDIO_VOICEPARAM_PAN, pan, t);
        audio_queueSetParam_f(voice->slot, AUDIO_VOICEPARAM_FADEOUTLEN, 0.0f, t);
    }
    else
    {
        // something else may have stolen the hardware voice
        emitter->voice = NULL;
    }
}

// attempt to assign a hardware voice to the given virtual voice
void assign_hw_voice(sound_emitter *emitter)
{
    sound_voice *voice = allocateVoice(emitter->priority);

    if (voice != NULL)
    {
        double t = audio_getTime();

        voice->playTime = t;
        voice->id++;

        emitter->voice = voice;
        emitter->id = voice->id;

        update_voice(emitter);

        queueStartVoice(voice->slot, t);
    }
}

void sound_playOneShot(uint8_t priority, sound_sample sample, uint8_t reverb, float volume, float pitch, float pan)
{
    sound_voice *voice = allocateVoice(priority);
    if (voice != NULL)
    {
        double t = audio_getTime();

        voice->playTime = t;
        voice->id++;

        audio_queueSetParam_i(voice->slot, AUDIO_VOICEPARAM_SAMPLEDATA, sample.handle, t);
        audio_queueSetParam_i(voice->slot, AUDIO_VOICEPARAM_SAMPLERATE, sample.samplerate, t);
        audio_queueSetParam_i(voice->slot, AUDIO_VOICEPARAM_LOOPENABLE, false, t);
        audio_queueSetParam_i(voice->slot, AUDIO_VOICEPARAM_RVBENABLE, reverb, t);
        audio_queueSetParam_f(voice->slot, AUDIO_VOICEPARAM_VOLUME, volume, t);
        audio_queueSetParam_f(voice->slot, AUDIO_VOICEPARAM_PITCH, pitch, t);
        audio_queueSetParam_f(voice->slot, AUDIO_VOICEPARAM_DETUNE, 0.0f, t);
        audio_queueSetParam_f(voice->slot, AUDIO_VOICEPARAM_PAN, pan, t);
        audio_queueSetParam_f(voice->slot, AUDIO_VOICEPARAM_FADEOUTLEN, 0.0f, t);

        queueStartVoice(voice->slot, t);
    }
}

sound_emitter *sound_play(uint8_t priority, sound_sample sample, uint8_t reverb, uint8_t loop, float volume, float pitch, float pan)
{
    sound_emitter *virtualVoice = (sound_emitter *)malloc(sizeof(sound_emitter));
    virtualVoice->isValid = true;
    virtualVoice->priority = priority;
    virtualVoice->id = 0;
    virtualVoice->sample = sample;
    virtualVoice->reverb = reverb;
    virtualVoice->loop = loop;
    virtualVoice->volume = volume;
    virtualVoice->pitch = pitch;
    virtualVoice->pan = pan;
    virtualVoice->is3D = false;
    virtualVoice->voice = NULL;
    virtualVoice->prev = NULL;
    virtualVoice->next = NULL;

    assign_hw_voice(virtualVoice);

    if (_ll_emitter_head == NULL)
    {
        _ll_emitter_head = virtualVoice;
        _ll_voice_tail = _ll_emitter_head;
    }
    else
    {
        _ll_voice_tail->next = virtualVoice;
        virtualVoice->prev = _ll_voice_tail;
        _ll_voice_tail = virtualVoice;
    }

    return virtualVoice;
}

sound_emitter *sound_play3D(uint8_t priority, sound_sample sample, uint8_t reverb, uint8_t loop, float volume, float pitch, Vec3 position, uint8_t attenModel, float attenMinDistance, float attenMaxDistance, float attenRolloff)
{
    sound_emitter *virtualVoice = (sound_emitter *)malloc(sizeof(sound_emitter));
    virtualVoice->isValid = true;
    virtualVoice->priority = priority;
    virtualVoice->id = 0;
    virtualVoice->sample = sample;
    virtualVoice->reverb = reverb;
    virtualVoice->loop = loop;
    virtualVoice->volume = volume;
    virtualVoice->pitch = pitch;
    virtualVoice->is3D = true;
    virtualVoice->position = position;
    virtualVoice->attenType = attenModel;
    virtualVoice->attenMinDist = attenMinDistance;
    virtualVoice->attenMaxDist = attenMaxDistance;
    virtualVoice->attenRolloff = attenRolloff;
    virtualVoice->voice = NULL;
    virtualVoice->prev = NULL;
    virtualVoice->next = NULL;

    assign_hw_voice(virtualVoice);

    if (_ll_emitter_head == NULL)
    {
        _ll_emitter_head = virtualVoice;
        _ll_voice_tail = _ll_emitter_head;
    }
    else
    {
        _ll_voice_tail->next = virtualVoice;
        virtualVoice->prev = _ll_voice_tail;
        _ll_voice_tail = virtualVoice;
    }

    return virtualVoice;
}

void sound_setPosition(sound_emitter *voice, Vec3 position)
{
    voice->position = position;
}

void sound_destroy(sound_emitter *voice)
{
    sound_stop(voice);
    free(voice);
}

void sound_stop(sound_emitter *voice)
{
    if (!voice->isValid)
        return;

    if (voice->voice != NULL && voice->id == voice->voice->id)
    {
        voice->voice->priority = 255;
        queueStopVoice(voice->voice->slot, 0.0);
    }

    voice->prev->next = voice->next;
    voice->next->prev = voice->prev;

    if (voice == _ll_emitter_head)
    {
        _ll_emitter_head = voice->next;
    }

    if (voice == _ll_voice_tail)
    {
        _ll_voice_tail = voice->prev;
    }

    voice->isValid = false;
}

void sound_init()
{
    _ll_emitter_head = NULL;
    _ll_voice_tail = NULL;

    for (int i = 0; i < 32; i++)
    {
        _voices[i].slot = i;
        _voices[i].priority = 255;
    }

    _listenerPos = (Vec3){0.0f, 0.0f, 0.0f};
    _listenerRot = QUATERNION_IDENTITY;
}

void sound_setListener(Vec3 pos, Quaternion rot)
{
    _listenerPos = pos;
    _listenerRot = rot;
}

void sound_update()
{
    // iterate virtual sound sources
    sound_emitter *curEmitter = _ll_emitter_head;
    while (curEmitter != NULL)
    {
        // virtual voice is still waiting for a hardware voice, try and assign one (if it's looping - otherwise just stop the voice from playing)
        // otherwise update hardware voice
        if (curEmitter->voice == NULL && curEmitter->loop)
        {
            assign_hw_voice(curEmitter);
        }
        else
        {
            update_voice(curEmitter);
        }

        if (!curEmitter->loop)
        {
            if (curEmitter->voice == NULL || audio_getVoiceState(curEmitter->voice->slot) == 0)
            {
                // something stole the hardware voice or the voice has stopped playing - stop the virtual voice and remove it from linked list
                sound_emitter *cur = curEmitter;
                curEmitter = curEmitter->next;
                sound_stop(cur);
                continue;
            }
        }

        curEmitter = curEmitter->next;
    }
}

sound_sample sound_loadWavBytes(const uint8_t *data)
{
    const uint8_t *reader = data;
    wavHeader header = *(wavHeader *)reader;
    reader += sizeof(wavHeader);

    // check RIFF string
    if (strncmp(header.riff, "RIFF", 4) || strncmp(header.wave, "WAVE", 4))
    {
        db_log("Input is not valid WAV file");
        return (sound_sample){-1, 0};
    }

    const uint8_t *reader_end = data + header.overall_size + 8;

    wavHeaderFmt headerFmt = *(wavHeaderFmt *)reader;
    reader += sizeof(wavHeaderFmt);

    // check fmt string
    if (strncmp(headerFmt.fmt_chunk_marker, "fmt ", 4))
    {
        db_log("Expected fmt chunk");
        return (sound_sample){-1, 0};
    }

    if (headerFmt.channels != 1)
    {
        db_log("Stereo wav files unsupported");
        return (sound_sample){-1, 0};
    }

    // skip over header data
    reader = data + sizeof(wavHeader) + headerFmt.length_of_fmt + 8;

    uint8_t dataFound = false;

    // start looking for data chunk
    wavChunkHeader chunkHeader;
    while (!dataFound && reader < reader_end)
    {
        chunkHeader = *(wavChunkHeader *)reader;
        reader += sizeof(wavChunkHeader);
        if (strncmp(&chunkHeader.id[0], "data", 4) == 0)
        {
            dataFound = true;
            break;
        }
        else
        {
            // skip chunk
            reader += chunkHeader.chunk_size;
        }
    }

    assert(dataFound && "No data chunk found in wav file");

    if (headerFmt.format_type == 1 && headerFmt.bits_per_sample == 8)
    {
        uint8_t *pcm8 = malloc(chunkHeader.chunk_size);
        memcpy(pcm8, reader, chunkHeader.chunk_size);

        // convert from unsigned 0 .. 255 to signed -128 .. 127
        for (int i = 0; i < chunkHeader.chunk_size; i++)
        {
            pcm8[i] -= 128;
        }

        int32_t sampleHandle = audio_alloc(pcm8, chunkHeader.chunk_size, AUDIO_FMT_PCM_S8);
        free(pcm8);
        return (sound_sample){
            sampleHandle,
            headerFmt.sample_rate};
    }
    else if (headerFmt.format_type == 1 && headerFmt.bits_per_sample == 16)
    {
        int16_t *pcm16 = malloc(chunkHeader.chunk_size);
        memcpy(pcm16, reader, chunkHeader.chunk_size);

        int32_t sampleHandle = audio_alloc(pcm16, chunkHeader.chunk_size, AUDIO_FMT_PCM_S16);
        free(pcm16);
        return (sound_sample){
            sampleHandle,
            headerFmt.sample_rate};
    }
    else if (headerFmt.format_type == 0x11)
    {
        // IMA ADPCM
        uint8_t *adpcm = malloc(chunkHeader.chunk_size);
        memcpy(adpcm, reader, chunkHeader.chunk_size);

        int32_t sampleHandle = audio_allocCompressed(adpcm, chunkHeader.chunk_size, headerFmt.block_align);
        free(adpcm);
        return (sound_sample){
            sampleHandle,
            headerFmt.sample_rate};
    }
    else
    {
        db_logf("Unsupported input format. format_type: %u bits_per_sample: %u", headerFmt.format_type, headerFmt.bits_per_sample);
        return (sound_sample){
            -1,
            0};
    }
}

sound_sample sound_loadWav(IOFILE *file)
{
    wavHeader header;
    fs_read(file, &header, sizeof(wavHeader));

    // check RIFF string
    if (strncmp(header.riff, "RIFF", 4) || strncmp(header.wave, "WAVE", 4))
    {
        db_log("Input is not valid WAV file");
        return (sound_sample){-1, 0};
    }

    wavHeaderFmt headerFmt;
    fs_read(file, &headerFmt, sizeof(wavHeaderFmt));

    // check fmt string
    if (strncmp(headerFmt.fmt_chunk_marker, "fmt ", 4))
    {
        db_log("Expected fmt chunk");
        return (sound_sample){-1, 0};
    }

    if (headerFmt.channels != 1)
    {
        db_log("Stereo wav files unsupported");
        return (sound_sample){-1, 0};
    }

    // skip over header data
    fs_seek(file, sizeof(wavHeader) + headerFmt.length_of_fmt + 8, IO_WHENCE_BEGIN);

    uint8_t dataFound = false;

    // start looking for data chunk
    wavChunkHeader chunkHeader;
    while (fs_read(file, &chunkHeader, sizeof(chunkHeader)) == sizeof(chunkHeader))
    {
        if (strncmp(&chunkHeader.id[0], "data", 4) == 0)
        {
            dataFound = true;
            break;
        }
        else
        {
            // skip chunk
            fs_seek(file, chunkHeader.chunk_size, IO_WHENCE_CURRENT);
        }
    }

    assert(dataFound && "No data chunk found in wav file");

    if (headerFmt.format_type == 1 && headerFmt.bits_per_sample == 8)
    {
        uint8_t *pcm8 = malloc(chunkHeader.chunk_size);
        fs_read(file, pcm8, chunkHeader.chunk_size);

        // convert from unsigned 0 .. 255 to signed -128 .. 127
        for (int i = 0; i < chunkHeader.chunk_size; i++)
        {
            pcm8[i] -= 128;
        }

        int32_t sampleHandle = audio_alloc(pcm8, chunkHeader.chunk_size, AUDIO_FMT_PCM_S8);
        free(pcm8);
        return (sound_sample){
            sampleHandle,
            headerFmt.sample_rate};
    }
    else if (headerFmt.format_type == 1 && headerFmt.bits_per_sample == 16)
    {
        int16_t *pcm16 = malloc(chunkHeader.chunk_size);
        fs_read(file, pcm16, chunkHeader.chunk_size);

        int32_t sampleHandle = audio_alloc(pcm16, chunkHeader.chunk_size, AUDIO_FMT_PCM_S16);
        free(pcm16);
        return (sound_sample){
            sampleHandle,
            headerFmt.sample_rate};
    }
    else if (headerFmt.format_type == 0x11)
    {
        // IMA ADPCM
        uint8_t *adpcm = malloc(chunkHeader.chunk_size);
        fs_read(file, adpcm, chunkHeader.chunk_size);

        int32_t sampleHandle = audio_allocCompressed(adpcm, chunkHeader.chunk_size, headerFmt.block_align);
        free(adpcm);
        return (sound_sample){
            sampleHandle,
            headerFmt.sample_rate};
    }
    else
    {
        db_logf("Unsupported input format. format_type: %u bits_per_sample: %u", headerFmt.format_type, headerFmt.bits_per_sample);
        return (sound_sample){
            -1,
            0};
    }
}