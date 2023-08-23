module dbsdk/gamepad

import std/num/int32

extern import
  c header-file "c/include/db_gamepad.h"

extern import
  c file "gamepad-inline"

abstract value struct gamepadState(boxed_ptr: any)

pub type gamepadButton
  A
  B
  X
  Y
  DPadUp
  DPadDown
  DPadLeft
  DPadRight
  L1
  L2
  L3
  R1
  R2
  R3
  Start
  Select

inline extern dbsdk-gamepad-isConnected(p: int32): int8
  c "gamepad_isConnected"

inline extern dbsdk-gamepad-readState(p: int32, gpad: any): ()
  c "kk_dbsdk_gamepad__gamepad_readState"

// NOTE: Type void in std/core/types is not public.
inline extern dbsdk-gamepad-setRumble(p: int32, on: int8): ()
  c "dbsdk_gamepad__gamepad_setRumble"

inline extern dbsdk-alloc-gamepadState(): any
  c "kk_dbsdk_gamepad__alloc_State"

inline extern dbsdk-gamepad-State-btnMask(gpad: any): int16
  c "kk_dbsdk_gamepad__State_btnMask"

inline extern dbsdk-gamepad-State-lStickX(gpad: any): int16
  c "kk_dbsdk_gamepad__State_lStickX"

inline extern dbsdk-gamepad-State-lStickY(gpad: any): int16
  c "kk_dbsdk_gamepad__State_lStickY"

inline extern dbsdk-gamepad-State-rStickX(gpad: any): int16
  c "kk_dbsdk_gamepad__State_rStickX"

inline extern dbsdk-gamepad-State-rStickY(gpad: any): int16
  c "kk_dbsdk_gamepad__State_rStickY"

// Koka has no uint16() function so we have to implement it manually for
// gamepadButton.
fun uint16(btn: gamepadButton): int16
  match btn
    A -> 1.int16()
    B -> 2.int16()
    X -> 4.int16()
    Y -> 8.int16()
    DPadUp -> 16.int16()
    DPadDown -> 32.int16()
    DPadLeft -> 64.int16()
    DPadRight -> 128.int16()
    L1 -> 256.int16()
    L2 -> 512.int16()
    L3 -> 1024.int16()
    R1 -> 2048.int16()
    R2 -> 4096.int16()
    R3 -> 8192.int16()
    Start -> 16384.int16()
    Select -> -32768.int16()


pub fun is-connected(port: int): bool
  match dbsdk-gamepad-isConnected(port.uint32()).int()
    1 -> True
    _ -> False

pub fun read-state(port: int, gamepad: gamepadState): ()
  dbsdk-gamepad-readState(port.uint32(), gamepad.boxed_ptr)

pub fun set-rumble(port: int, enabled: bool): ()
  val c_bool = match enabled
    True -> 1
    False -> 0
  dbsdk-gamepad-setRumble(port.uint32(), c_bool.int8())
  return ()

pub fun alloc-gamepadState(): gamepadState
  GamepadState(dbsdk-alloc-gamepadState())

// Return int32 for access to the bitwise functions.
pub fun btn-mask(gamepad: gamepadState): int32
  dbsdk-gamepad-State-btnMask(gamepad.boxed_ptr).int().uint32()

pub fun lstick-x(gamepad: gamepadState): int
  dbsdk-gamepad-State-lStickX(gamepad.boxed_ptr).int()

pub fun lstick-y(gamepad: gamepadState): int
  dbsdk-gamepad-State-lStickY(gamepad.boxed_ptr).int()

pub fun rstick-x(gamepad: gamepadState): int
  dbsdk-gamepad-State-rStickX(gamepad.boxed_ptr).int()

pub fun rstick-y(gamepad: gamepadState): int
  dbsdk-gamepad-State-rStickY(gamepad.boxed_ptr).int()