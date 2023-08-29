import dbsdk/dbsdk
import dbsdk/log
import dbsdk/vdp
import std/num/int32

struct gamestate(bg: color32, r: rect, texh: int32)

fun tick(st: gamestate): _ gamestate
  clear-color(st.bg)
  val r = st.r
  db-log("Rect: " ++ r.x.show ++ ", " ++ r.y.show ++ ", " ++ r.w.show ++ ", " ++ r.h.show)
  db-log("Memory Usage: " ++ get-usage().show)
  //clear-depth
  //depth-write
  //depth-func
  //r(bg)
  //g(bg)
  //b(bg)
  //a(bg)
  
  val texh = st.texh
  if texh == zero then
    st(texh = alloc-texture(False, RGBA8888, 256, 1))
  else
    st

fun main()
  db-log("Test db_vdp")
  db-log("===========")
  db-log("")
  
  initialize(Gamestate(alloc-color32(255, 128, 255, 255), alloc-rect(1, 2, 3, 4), 0.int32()))
  set-vsync-handler(tick)