import dbsdk/dbsdk
import dbsdk/clock
import dbsdk/log
import dbsdk/vdp

// Test effects
type xory
    X
    Y

effect val bg-color: color32
effect vertices
    fun x-or-y(which: xory): vertex
    ctl z(): vertex

ref struct gameState
    num: int = 0
    msg: string = "Hello, DreamBox!"
    color: color32
    triangle: vector<vertex>

fun tick(game-state: gameState): _ gameState
    clear-color(game-state.color) // Effect `bg-color`
    draw-geometry(game-state.triangle)
    val currnum = game-state.num
    db-log("Current State: " ++ currnum.show)
    game-state(num = currnum + 1)

fun main()
    clock-getTimestamp() // Needed by Koka.
    with val bg-color = Color32(128, 128, 255, 255)
    with handler
        fun x-or-y(which)
            match which
                X -> Vertex(Vec4( 0.0,  0.5, 0.0, 1.0), Vec4(1.0, 0.0, 0.0, 1.0))
                Y -> Vertex(Vec4(-0.5, -0.5, 0.0, 1.0), Vec4(0.0, 1.0, 0.0, 1.0))
        ctl z()
            // return ... also works! Needs more complex example to demo.
            resume(Vertex(Vec4( 0.5, -0.5, 0.0, 1.0), Vec4(0.0, 0.0, 1.0, 1.0)))
    // Here we go...
    val verts = [x-or-y(X), x-or-y(Y), z()]
    // Note that bg-color is saved to the GameState. The tick function would
    // not be able to rely on the `with val` handler above since the main func
    // exits before DreamBox starts calling the tick callback.
    initialize(GameState(0, "Hello, World!", bg-color, verts.vector()))
    set-vsync-handler(tick)
    db-log("Tick Registered!")

    return 0