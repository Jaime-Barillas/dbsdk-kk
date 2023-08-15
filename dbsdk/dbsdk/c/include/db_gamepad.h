#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define GAMEPAD_BTN_A (1 << 0)
#define GAMEPAD_BTN_B (1 << 1)
#define GAMEPAD_BTN_X (1 << 2)
#define GAMEPAD_BTN_Y (1 << 3)
#define GAMEPAD_BTN_DPAD_UP (1 << 4)
#define GAMEPAD_BTN_DPAD_DOWN (1 << 5)
#define GAMEPAD_BTN_DPAD_LEFT (1 << 6)
#define GAMEPAD_BTN_DPAD_RIGHT (1 << 7)
#define GAMEPAD_BTN_L1 (1 << 8)
#define GAMEPAD_BTN_L2 (1 << 9)
#define GAMEPAD_BTN_L3 (1 << 10)
#define GAMEPAD_BTN_R1 (1 << 11)
#define GAMEPAD_BTN_R2 (1 << 12)
#define GAMEPAD_BTN_R3 (1 << 13)
#define GAMEPAD_BTN_START (1 << 14)
#define GAMEPAD_BTN_SELECT (1 << 15)

/// @brief Represents current input state of a gamepad
typedef struct
{
    /// @brief Bitmask of currently pressed buttons. Refer to GAMEPAD_BTN_* mask defines to check these bits
    uint16_t btnMask;

    /// @brief The X position of the left stick, as a value between -32767 and +32767
    int16_t lStickX;

    /// @brief The Y position of the left stick, as a value between -32767 and +32767
    int16_t lStickY;

    /// @brief The X position of the right stick, as a value between -32767 and +32767
    int16_t rStickX;

    /// @brief The Y position of the right stick, as a value between -32767 and +32767
    int16_t rStickY;
} gamepad_State;

/// @brief Check if a gamepad is connected to the given port
/// @param port The port to check (0 to 3)
/// @return 1 if the gamepad is connected, false otherwise
extern uint8_t gamepad_isConnected(uint32_t port);

/// @brief Read the state of the gamepad connected to the given port
/// @param port The port to check (0 to 3)
/// @param state Pointer to the struct to fill with the current gamepad state
extern void gamepad_readState(uint32_t port, gamepad_State *state);

/// @brief Set rumble enabled or disabled on the gamepad connected to the given port
/// @param port THe port to check (0 to 3)
/// @param enable Whether to enable rumble
extern void gamepad_setRumble(uint32_t port, uint8_t enable);

#ifdef __cplusplus
}
#endif