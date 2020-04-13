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
  readFileSync("./test/simple.svg", `utf8)->testAll
);

describe("edge case width svg", () =>
  readFileSync("./test/edge-case-width.svg", `utf8)->testAll
);

describe("clean & minimal svg", () =>
  readFileSync("./test/clean.svg", `utf8)->testAll
);

describe("sketch export", () =>
  readFileSync("./test/sketch-export.svg", `utf8)->testAll
);

describe("with fill", () =>
  readFileSync("./test/with-fill.svg", `utf8)->testAll
);

describe("with stroke", () =>
  readFileSync("./test/with-stroke.svg", `utf8)->testAll
);
