open Node.Fs

open Jest
open Expect

let fixtures = "./__tests__/__fixtures__"

let snap = (~removeFill=false, ~removeStroke=false, svg) =>
  svg
  ->Transformer.transformSvg(
    ~removeFill,
    ~removeStroke,
    ~js=false,
    ~pascalCaseTag=true,
    ~template=Templates.nativeForRescript,
  )
  ->expect
  ->toMatchSnapshot

let testAll = svg => {
  test("all options", () => svg->snap(~removeFill=true, ~removeStroke=true))
  test("remove-fill", () => svg->snap(~removeFill=true, ~removeStroke=false))
  test("remove-stroke", () => svg->snap(~removeFill=false, ~removeStroke=true))
}

describe("simple svg", () => readFileSync(fixtures ++ "/simple.svg", #utf8)->testAll)

describe("edge case width svg", () =>
  readFileSync(fixtures ++ "/edge-case-width.svg", #utf8)->testAll
)

describe("clean & minimal svg", () => readFileSync(fixtures ++ "/clean.svg", #utf8)->testAll)

describe("sketch export", () => readFileSync(fixtures ++ "/sketch-export.svg", #utf8)->testAll)

describe("with fill", () => readFileSync(fixtures ++ "/with-fill.svg", #utf8)->testAll)

describe("with stroke", () => readFileSync(fixtures ++ "/with-stroke.svg", #utf8)->testAll)

describe("rescript native svg tweaks", () => {
  test("%", () => j`<svg><circle cx="2%" /></svg>`->snap)

  test("% with decimals", () => j`<svg><circle cx="2.45%" /></svg>`->snap)

  test("% negative", () => j`<svg><circle cx="-2%" /></svg>`->snap)

  test("% negative with decimals", () => j`<svg><circle cx="-2.001%" /></svg>`->snap)

  test("float", () => j`<svg><circle cx="2" /></svg>`->snap)
  test("float with decimals", () => j`<svg><circle cx="12.96" /></svg>`->snap)
  test("float with only decimals", () => j`<svg><stop offset=".9" /></svg>`->snap)
  test("matrix", () =>
    j`<svg><radialGradient gradientTransform="matrix(.38431685 -.92316433 .92320126 .38430148 -.987558 .951797)" /><radialGradient gradientTransform="matrix(0 1 0.1 1.0 -1 -.1)" /></svg>`->snap
  )
})
