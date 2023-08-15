#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define AUDIO_VOICEPARAM_VOLUME     0
#define AUDIO_VOICEPARAM_PITCH      1
#define AUDIO_VOICEPARAM_DETUNE     2
#define AUDIO_VOICEPARAM_PAN        3
#define AUDIO_VOICEPARAM_SAMPLEDATA 4
#define AUDIO_VOICEPARAM_SAMPLERATE 5
#define AUDIO_VOICEPARAM_LOOPENABLE 6
#define AUDIO_VOICEPARAM_LOOPSTART  7
#define AUDIO_VOICEPARAM_LOOPEND    8
#define AUDIO_VOICEPARAM_RVBENABLE  9
#define AUDIO_VOICEPARAM_FADEINLEN  10
#define AUDIO_VOICEPARAM_FADEOUTLEN 11

#define AUDIO_FMT_PCM_S8    0
#define AUDIO_FMT_PCM_S16   1

/// @brief Upload sample data to the audio system
/// @param dataPtr Pointer to the audio data to upload
/// @param dataLen Length of the audio data buffer
/// @param audioFmt Format of the data to upload (valid values are AUDIO_FMT_PCM_S8 or AUDIO_FMT_PCM_S16)
/// @return A handle to the allocated sample data, or -1 if allocation failed
extern int32_t audio_alloc(const void *dataPtr, uint32_t dataLen, uint32_t audioFmt);

/// @brief Upload IMA ADPCM compressed sample data to the audio system
/// @param dataPtr Pointer to the audio data to upload
/// @param dataLen Length of the audio data buffer
/// @param blockSize Length of each block of data
/// @return A handle to the allocated sample data, or -1 if allocation failed
extern int32_t audio_allocCompressed(const void *dataPtr, uint32_t dataLen, uint32_t blockSize);

/// @brief Free previously allocated sample data
/// @param handle A handle previously returned from audio_alloc
extern void audio_free(int32_t handle);

/// @brief Get total audio memory usage
/// @return Total audio memory usage in bytes
extern uint32_t audio_getUsage();

/// @brief Get the state of the voice in the given slot
/// @param slot The voice slot (0 to 31)
/// @return 1 if the voice is currently playing, 0 otherwise
extern uint8_t audio_getVoiceState(uint32_t slot);

/// @brief Schedule parameter change for voice in the given slot
/// @param slot The voice slot (0 to 31)
/// @param param The parameter to change (one of the AUDIO_VOICEPARAM_* enumerations)
/// @param value The value to set the parameter to
/// @param time The time at which to change the parameter
extern void audio_queueSetParam_i(uint32_t slot, uint32_t param, int32_t value, double time);

/// @brief Schedule parameter change for voice in the given slot
/// @param slot The voice slot (0 to 31)
/// @param param The parameter to change (one of the AUDIO_VOICEPARAM_* enumerations)
/// @param value The value to set the parameter to
/// @param time The time at which to change the parameter
extern void audio_queueSetParam_f(uint32_t slot, uint32_t param, float value, double time);

/// @brief Schedule voice in the given slot to start playing
/// @param slot The voice slot (0 to 31)
/// @param time The time at which to start playing
extern void audio_queueStartVoice(uint32_t slot, double time);

/// @brief Schedule voice in the given slot to stop playing
/// @param slot The voice slot (0 to 31)
/// @param time The time at which to stop playing
extern void audio_queueStopVoice(uint32_t slot, double time);

/// @brief Get the current audio time
/// @return A time which can be used to schedule voice parameter changes
extern double audio_getTime();

/// @brief Set the global reverb unit parameters for voices with reverb enabled
/// @param roomSize The room size (values >1 may be unstable. default is 0.5)
/// @param damp Damping to apply (default is 0.5)
/// @param width Stereo width of the reverb (default is 1.0)
/// @param wet The gain of the wet signal (default is 0.2)
/// @param dry The gain of the dry signal (default is 0.8)
extern void audio_setReverbParams(float roomSize, float damp, float width, float wet, float dry);

/// @brief Initialize the MIDI synthesis engine with a soundfont
/// @param sf2Data Pointer to the SF2 data to load
/// @param sf2DataLen Length of the SF2 data blob
/// @returns False if an error occurred, true otherwise
extern uint8_t audio_initSynth(void *sf2Data, uint32_t sf2DataLen);

/// @brief Begin playing the given MIDI data via the synthesis engine
/// @param smfData Pointer to the standard midi file data to load
/// @param smfDataLen Length of the standard midi file data blob
/// @param loop Whether to loop midi playback to either the beginning or a specified loop point (marked with CC#111)
/// @returns False if an error occurred, true otherwise
extern uint8_t audio_playMidi(void *smfData, uint32_t smfDataLen, uint8_t loop);

/// @brief Set volume of MIDI playback
/// @param volume New volume to set
extern void audio_setMidiVolume(float volume);

/// @brief Set whether MIDI synthesis engine routes through globl reverb unit
/// @param enabled true to enable reverb, false otherwise
extern void audio_setMidiReverb(uint8_t enabled);

#ifdef __cplusplus
}
#endif