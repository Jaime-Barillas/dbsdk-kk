import dbsdk/dbsdk
import dbsdk/log
import dbsdk/gamepad
import dbsdk/vdp
import std/num/int32

fun tick(gpad: gamepadState): _ gamepadState
  read-state(0, gpad)
  //db-log("Setting rumble...")
  //set-rumble(0, True)
  
  val btns = btn-mask(gpad)
  val lx = lstick-x(gpad)
  val ly = lstick-y(gpad)
  val rx = rstick-x(gpad)
  val ry = rstick-y(gpad)

  if btns != zero then
    db-log("btn-mask(): " ++ btns.show)
  if lx != 0 then
    db-log("lstick-x(): " ++ lx.show)
  if ly != 0 then
    db-log("lstick-y(): " ++ ly.show)
  if rx != 0 then
    db-log("rstick-x(): " ++ rx.show)
  if ry != 0 then
    db-log("rstick-y(): " ++ ry.show)

  gpad

fun main()
  db-log("Test db_gamepad")
  db-log("===============")
  db-log("")

  db-log("is-connected(0): " ++ is-connected(0).show)
  db-log("is-connected(1): " ++ is-connected(1).show)
  db-log("is-connected(2): " ++ is-connected(2).show)
  db-log("is-connected(3): " ++ is-connected(3).show)
  
  initialize(alloc-gamepadState())
  set-vsync-handler(tick)
