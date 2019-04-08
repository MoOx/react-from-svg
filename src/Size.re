// 100.->pct needs to be 100%  & not 100.% (for web compat at least),
// so we go for 100.0% (simple method, almost cost compared to printf or whatever)
let pctString = num => num->Js.Float.toString ++ "0%";

type t = string;

external pt: float => t = "%identity";
let pct: float => t = pctString->Obj.magic;
