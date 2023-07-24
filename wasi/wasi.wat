(module
  (type (;0;) (func (param i32 i32) (result i32)))
  (type (;1;) (func (result i64)))
  (type (;2;) (func))
  (type (;3;) (func (param i32)))
  (type (;4;) (func (param i32 i64 i32) (result i32)))
  (type (;5;) (func (param i32) (result i32)))
  (type (;6;) (func (param i32 i32 i32 i32) (result i32)))
  (type (;7;) (func (param i32 i64 i32 i32) (result i32)))
  (import "env" "clock_getTimestamp" (func (;0;) (type 1)))
  (import "env" "memory" (memory (;0;) 0))
  (func (;1;) (type 2)
    nop)
  (func (;2;) (type 0) (param i32 i32) (result i32)
    local.get 0
    i32.const 0
    i32.store
    local.get 1
    i32.const 0
    i32.store
    i32.const 0)
  (func (;3;) (type 0) (param i32 i32) (result i32)
    i32.const 0)
  (func (;4;) (type 3) (param i32)
    nop)
  (func (;5;) (type 4) (param i32 i64 i32) (result i32)
    (local i32)
    i32.const 56269
    local.set 3
    local.get 0
    i32.const 1
    i32.eq
    if (result i32)  ;; label = @1
      local.get 2
      call 0
      i64.const 1000000000
      i64.mul
      i64.store
      i32.const 0
    else
      local.get 3
    end)
  (func (;6;) (type 0) (param i32 i32) (result i32)
    (local i32)
    i32.const 28
    local.set 2
    local.get 0
    i32.const 1
    i32.eq
    if (result i32)  ;; label = @1
      local.get 1
      i64.const 1000000000
      i64.store
      i32.const 0
    else
      local.get 2
    end)
  (func (;7;) (type 5) (param i32) (result i32)
    i32.const 0)
  (func (;8;) (type 6) (param i32 i32 i32 i32) (result i32)
    i32.const -1)
  (func (;9;) (type 7) (param i32 i64 i32 i32) (result i32)
    i32.const -1)
  (export "__wasm_call_ctors" (func 1))
  (export "__wasm_apply_data_relocs" (func 1))
  (export "args_sizes_get" (func 2))
  (export "args_get" (func 3))
  (export "proc_exit" (func 4))
  (export "clock_time_get" (func 5))
  (export "clock_res_get" (func 6))
  (export "environ_sizes_get" (func 2))
  (export "environ_get" (func 3))
  (export "fd_close" (func 7))
  (export "fd_read" (func 8))
  (export "fd_write" (func 8))
  (export "fd_seek" (func 9)))
