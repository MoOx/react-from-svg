let pctString = num => num->Js.Float.toString ++ "%";

type t = string;

[@deprecated "Use `dp` instead"] external pt: float => t = "%identity";

external dp: float => t = "%identity";

let pct: float => t = pctString->Obj.magic;
