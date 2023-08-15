#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define BIOS_VIDEOMODE_DEFAULT 0
#define BIOS_VIDEOMODE_VGA 1
#define BIOS_VIDEOMODE_COMPOSITE 2
#define BIOS_VIDEOMODE_SVIDEO 3

/// @brief Load a program and begin executing
/// @param codeData Pointer to the WASM code blob in memory
/// @param codeLen Length of the WASM code blob
extern void bios_loadProgram(const void *codeData, uint32_t codeLen);

/// @brief Get the currently set console language from BIOS settings
/// @param outLangStr Pointer to a string which will be filled with an ISO language code ("en", "fr", "es", "ja", etc)
extern void bios_getPrefLang(char *outLangStr);

/// @brief Set the current console language to the given ISO language code
/// @param langStr An ISO language code to set ("en", "fr", "es", "ja", etc)
extern void bios_setPrefLang(const char *langStr);

/// @brief Get the currently set console audio volume from BIOS settings
/// @return The current audio volume (0.0 .. 1.0)
extern float bios_getPrefAudioVolume();

/// @brief Set the console audio volume
/// @param value A new audio volume to assign (0.0 .. 1.0)
extern void bios_setPrefAudioVolume(float value);

/// @brief Get the current console video output mode from BIOS settings
/// @return A video output mode (refer to BIOS_VIDEOMODE_* defines)
extern uint32_t bios_getPrefVideoOutput();

/// @brief Set the current console video output mode
/// @param videoOutputMode A video output mode (refer to BIOS_VIDEOMODE_* defines)
extern void bios_setPrefVideoOutput(uint32_t videoOutputMode);

/// @brief Get whether the console is set to display a 24hr clock from BIOS settings
/// @return True if the console displays a 24-hour clock, false if it displays a 12-hour clock
extern uint8_t bios_getPref24HrClock();

/// @brief Set whether the console should display a 24hr clock
/// @param enable True if the console should display a 24-hour clock, false if it should display a 12-hour clock
extern void bios_setPref24HrClock(uint8_t enable);

/// @brief Persist preference settings
extern void bios_savePrefs();

#ifdef __cplusplus
}
#endif