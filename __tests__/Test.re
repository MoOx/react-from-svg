open Node.Fs;

open Jest;
open Expect;

let snap = (svg, ~removeFill, ~removeStroke) => {
  svg
  ->Transformer.transformSvg(
      ~removeFill,
      ~removeStroke,
      ~commonjs=false,
      ~pascalCaseTag=true,
      ~template=Templates.native,
    )
  ->expect
  ->toMatchSnapshot;
};

let testAll = svg => {
  test("all options", () =>
    svg->snap(~removeFill=true, ~removeStroke=true)
  );
  test("remove-fill", () =>
    svg->snap(~removeFill=true, ~removeStroke=false)
  );
  test("remove-stroke", () =>
    svg->snap(~removeFill=false, ~removeStroke=true)
  );
};

describe("simple svg", () =>
  readFileSync("./__tests__/fixtures/simple.svg", `utf8)->testAll
);

describe("edge case width svg", () =>
  readFileSync("./__tests__/fixtures/edge-case-width.svg", `utf8)->testAll
);

describe("clean & minimal svg", () =>
  readFileSync("./__tests__/fixtures/clean.svg", `utf8)->testAll
);

describe("sketch export", () =>
  readFileSync("./__tests__/fixtures/sketch-export.svg", `utf8)->testAll
);

describe("with fill", () =>
  readFileSync("./__tests__/fixtures/with-fill.svg", `utf8)->testAll
);

describe("with stroke", () =>
  readFileSync("./__tests__/fixtures/with-stroke.svg", `utf8)->testAll
);
