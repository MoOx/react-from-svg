open Node.Fs;

open Jest;
open Expect;

let fixtures = "./__tests__/__fixtures__";

let snap = (svg, ~removeFill, ~removeStroke) => {
  svg
  ->Transformer.transformSvg(
      ~removeFill,
      ~removeStroke,
      ~js=false,
      ~pascalCaseTag=true,
      ~template=Templates.nativeForReason,
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
  readFileSync(fixtures ++ "/simple.svg", `utf8)->testAll
);

describe("edge case width svg", () =>
  readFileSync(fixtures ++ "/edge-case-width.svg", `utf8)->testAll
);

describe("clean & minimal svg", () =>
  readFileSync(fixtures ++ "/clean.svg", `utf8)->testAll
);

describe("sketch export", () =>
  readFileSync(fixtures ++ "/sketch-export.svg", `utf8)->testAll
);

describe("with fill", () =>
  readFileSync(fixtures ++ "/with-fill.svg", `utf8)->testAll
);

describe("with stroke", () =>
  readFileSync(fixtures ++ "/with-stroke.svg", `utf8)->testAll
);
