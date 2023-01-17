open Node.Fs

open Jest
open Expect

let fixtures = "./__tests__/__fixtures__"

let snap = (svg, ~name, ~removeFill, ~removeStroke) =>
  svg
  ->Transformer.transformSvg(
    ~removeFill,
    ~removeStroke,
    ~js=true,
    ~pascalCaseTag=true,
    ~template=Templates.native(~commonjs=false, ~name),
  )
  ->expect
  ->toMatchSnapshot

let testAll = (~name, svg) => {
  test("all options", () => svg->snap(~name, ~removeFill=true, ~removeStroke=true))
  test("remove-fill", () => svg->snap(~name, ~removeFill=true, ~removeStroke=false))
  test("remove-stroke", () => svg->snap(~name, ~removeFill=false, ~removeStroke=true))
}

describe("simple svg", () =>
  readFileSync(fixtures ++ "/simple.svg", #utf8)->testAll(~name="Simple")
)

describe("edge case width svg", () =>
  readFileSync(fixtures ++ "/edge-case-width.svg", #utf8)->testAll(~name="EdgeCaseWidth")
)

describe("clean & minimal svg", () =>
  readFileSync(fixtures ++ "/clean.svg", #utf8)->testAll(~name="Clean")
)

describe("sketch export", () =>
  readFileSync(fixtures ++ "/sketch-export.svg", #utf8)->testAll(~name="SketchExport")
)

describe("with fill", () =>
  readFileSync(fixtures ++ "/with-fill.svg", #utf8)->testAll(~name="WithFill")
)

describe("with stroke", () =>
  readFileSync(fixtures ++ "/with-stroke.svg", #utf8)->testAll(~name="WithStroke")
)
