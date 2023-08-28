module dbsdk/gamepad

import std/num/int32

extern import
  c header-file "c/include/db_gamepad.h"

extern import
  c file "gamepad-inline"

abstract value struct gamepadState(boxed_ptr: any)

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