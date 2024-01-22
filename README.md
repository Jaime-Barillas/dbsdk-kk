# dbsdk-kk

Cli tool + wrapper over the [DreamBox](https://dreambox3d.dev) SDK API for
[Koka](https://koka-lang.github.io/koka/doc/index.html).

# Progress

## Cli

|Component      |Done?           |
|---------------|----------------|
|`new` command  |&#x274c;        |
|`build` command|&#x274c;        |
|`clean` command|&#x274c;        |

## DBSDK

<table>
  <tr> <th>File</th> <th>Done?</th> <th>Notes</th> </tr>
  <tr>
    <td>db_audio.h</td>
    <td>&#x274c;</td>
    <td>Includes stdint.h</td>
  </tr>
  <tr>
    <td>db_bios.h</td>
    <td>&#x274c;</td>
    <td>Includes stdint.h</td>
  </tr>
  <tr>
    <td>db_clock.h</td>
    <td>&#x2714;&#xfe0f;</td>
    <td></td>
  </tr>
  <tr>
    <td>db_gamepad.h</td>
    <td>&#x2714;&#xfe0f;</td>
    <td></td>
  </tr>
  <tr>
    <td>db_io.h</td>
    <td>&#x274c;</td>
    <td>Includes stdint.h</td>
  </tr>
  <tr>
    <td>db_log.h</td>
    <td>~</td>
    <td>
      <code>db_log</code> has a Koka wrapper,
      <code>db_logf</code> is not available in Koka
    </td>
  </tr>
  <tr>
    <td>db_log.c</td>
    <td>&#x274c;</td>
    <td><code>db_logf</code> is not available in Koka</td>
  </tr>
  <tr>
    <td>db_math.h</td>
    <td>&#x274c;</td>
    <td>Includes stdint.h</td>
  </tr>
  <tr>
    <td>db_math.c</td>
    <td>&#x274c;</td>
    <td>Includes db_log.h</td>
  </tr>
  <tr>
    <td>db_sounddriver.h</td>
    <td>&#x274c;</td>
    <td>Includes stdint.h, db_math.h, db_io.h</td>
  </tr>
  <tr>
    <td>db_sounddriver.c</td>
    <td>&#x274c;</td>
    <td>Includes stdbool.h, stdlib.h, errno.h, string.h, math.h, assert.h, db_audio.h, db_io.h, db_log.h</td>
  </tr>
  <tr>
    <td>db_vdp.h</td>
    <td>&#x274c;</td>
    <td>
      Includes stdint.h, db_math.h (Only Vec4 is required.)</br>
      Contains additional fns to set initial state. These are to be moved at a later time.
    </td>
  </tr>
</table>

# Documentation

TODO

# License

TBD