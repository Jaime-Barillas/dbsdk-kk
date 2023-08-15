#pragma once

#include <stdint.h>

#include "db_math.h"
#include "db_io.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define SOUND_ATTEN_NONE 0
#define SOUND_ATTEN_INV_DISTANCE 1
#define SOUND_ATTEN_LINEAR 2
#define SOUND_ATTEN_EXP_DISTANCE 3

/// @brief Represents a loaded sound sample
typedef struct
{
    int32_t handle;
    uint32_t samplerate;
} sound_sample;

struct sound_emitter;
struct sound_voice;

/// @brief Struct containing the state of a sound emitter
typedef struct sound_emitter
{
    uint8_t isValid;
    uint8_t priority;
    uint8_t loop;
    uint8_t reverb;
    uint8_t is3D;
    uint8_t attenType;
    float attenMinDist;
    float attenMaxDist;
    float attenRolloff;
    Vec3 position;
    float volume;
    float pitch;
    float pan;
    sound_sample sample;
    uint32_t id;
    struct sound_voice *voice;
    struct sound_emitter *prev;
    struct sound_emitter *next;
} sound_emitter;

/// @brief Initialize the sound driver
void sound_init();

/// @brief Update sound playback
void sound_update();

/// @brief Load a sample from a .WAV file
/// @param file Handle to the open WAV file
/// @return The loaded sample handle
sound_sample sound_loadWav(IOFILE *file);

/// @brief Load a sample from a .WAV file blob
/// @param data Pointer to the wav file bytes
/// @return The loaded sample handle
sound_sample sound_loadWavBytes(const uint8_t *data);

/// @brief Play a one-shot sample
/// @param priority The priority of the sound (0 is highest, 255 is lowest)
/// @param sample The sample to play
/// @param reverb Whether to apply reverb to the sound
/// @param volume The volume of the sound
/// @param pitch The pitch of the sound
/// @param pan The pan of the sound
void sound_playOneShot(uint8_t priority, sound_sample sample, uint8_t reverb, float volume, float pitch, float pan);

/// @brief Play a one-shot sample in 3D
/// @param priority The priority of the sound (0 is highest, 255 is lowest)
/// @param sample The sample to play
/// @param reverb Whether to apply reverb to the sound
/// @param volume The volume of the sound
/// @param pitch The pitch of the sound
/// @param position The position of the sound
/// @param attenModel The attenuation model of the sound
/// @param attenMinDistance The min distance of the sound
/// @param attenMaxDistance The max distance of the sound
/// @param attenRolloff The rolloff factor of the sound
void sound_playOneShot3D(uint8_t priority, sound_sample sample, uint8_t reverb, float volume, float pitch, Vec3 position, uint8_t attenModel, float attenMinDistance, float attenMaxDistance, float attenRolloff);

/// @brief Begin playing a sound, returning a pointer to the emitter
/// @param priority The priority of the sound (0 is highest, 255 is lowest)
/// @param sample The sample to play
/// @param reverb Whether to apply reverb to the sound
/// @param loop Whether to loop the sample
/// @param volume The initial volume
/// @param pitch The initial pitch
/// @param pan The initial pan
/// @return A pointer to the virtual voice
sound_emitter *sound_play(uint8_t priority, sound_sample sample, uint8_t reverb, uint8_t loop, float volume, float pitch, float pan);

/// @brief Begin playing a 3D sound, returning a pointer to the emitter
/// @param priority The priority of the sound (0 is highest, 255 is lowest)
/// @param sample The sample to play
/// @param reverb Whether to apply reverb to the sound
/// @param loop Whether to loop the sample
/// @param volume The initial volume
/// @param pitch The initial pitch
/// @param position The initial position of the emitter
/// @param attenModel The attenuation model of the emitter
/// @param attenMinDistance The min distance of the emitter
/// @param attenMaxDistance The max distance of the emitter
/// @param attenRolloff The rolloff factor of the emitter
/// @return A pointer to the virtual voice
sound_emitter *sound_play3D(uint8_t priority, sound_sample sample, uint8_t reverb, uint8_t loop, float volume, float pitch, Vec3 position, uint8_t attenModel, float attenMinDistance, float attenMaxDistance, float attenRolloff);

/// @brief Destroy the sound emitter
/// @param voice The emitter handle
void sound_destroy(sound_emitter *voice);

/// @brief Stop playing the sound emitter
/// @param voice A pointer to the emitter
void sound_stop(sound_emitter *voice);

/// @brief Update the position of the emitter
/// @param voice The emitter to update
/// @param position The new position
void sound_setPosition(sound_emitter *voice, Vec3 position);

/// @brief Set the position and orientation of the listener
/// @param listenerPosition The position of the listener
/// @param listenerOrientation The orientation of the listener
void sound_setListener(Vec3 listenerPosition, Quaternion listenerOrientation);

#ifdef __cplusplus
}
#endif