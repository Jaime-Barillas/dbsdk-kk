/*==============================================================================
 Wasm Types
 ----------
 An assortment of types, some used by the parser, others by the patcher, some by
 both.
 =============================================================================*/
module wat/types

pub type wasm-type
  I32
  I64
  F32
  F64

pub struct func-type
  params: list<wasm-type>
  result: list<wasm-type>

pub type module-field
  Module(src: string)
  Type(src: string, idx: int, typ: func-type)
  Import(src: string, idx: int, typ-idx: int, name: string)
  Func(src: string, idx: int, typ-idx: int, name: maybe<string>)
  Table(src: string)
  Memory(src: string)
  Global(src: string)
  Export(src: string)
  Start(src: string)
  Elem(src: string)
  Data(src: string)
  Other(src: string)

// Common Operations

pub fun show(wtype: wasm-type): string
  match wtype
    I32 -> "I32"
    I64 -> "I64"
    F32 -> "F32"
    F64 -> "F64"

pub fun show(typ: func-type): string
  join(["(params: ",
        show-list(typ.params, show),
        ", result: ",
        show-list(typ.result, show),
        ")"])

pub fun show(field: module-field): string
  match field
    Module(_) -> "Module"
    Type(_, idx, typ) -> ["Type(", idx.show, ", ", typ.show, ")"].join
    Import(_, idx, typ-idx, name) ->
      join(["Import(", idx.show, ", ", typ-idx.show, ", ", name, ")"])
    Func(_, idx, typ-idx, name) ->
      join(["Func(", idx.show, ", ", typ-idx.show, ", ", name.default("<no-name>"), ")"])
    Table -> "Table"
    Memory -> "Memory"
    Global -> "Global"
    Export -> "Export"
    Start -> "Start"
    Elem -> "Elem"
    Data -> "Data"
    Other -> "Other"