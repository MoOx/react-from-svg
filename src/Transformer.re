open Node;
open Belt;

[@bs.module "mkdirp"] external mkdirpSync: string => unit = "sync";
type camelCaseOptions = {pascalCase: bool};
[@bs.module]
external camelCase: (string, camelCaseOptions) => string = "camelcase";

let root = Process.cwd();
let sep = Path.sep;

type file = {
  name: string,
  content: string,
};

let get = (globPattern: string) => {
  globPattern
  ->Glob.glob
  ->Future.mapOk(SortArray.String.stableSort)
  ->Future.mapOk(Array.reverse)
  ->Future.mapOk(files =>
      files->Array.map(item =>
        {name: item, content: Fs.readFileAsUtf8Sync(item)}
      )
    );
};

let shortenFilenames = (sourcePath, files) => {
  files->Array.map(file =>
    {
      ...file,
      name:
        (
          file.name
          |> Js.String.replace(sourcePath ++ "/", "")
          |> Js.String.replace(".svg", "")
        )
        ->camelCase({pascalCase: true}),
    }
  );
};

let noop = s => s;

let transformSvg =
    (svg, ~removeFill, ~removeStroke, ~commonjs, ~template, ~pascalCaseTag) =>
  AdjustSvg.(
    svg
    ->cleanupStart
    ->prepareProps
    ->dashToCamelCaseProps
    ->(pascalCaseTag ? tagToPascalCase : noop)
    ->cleanupEnd
    ->(removeFill ? deleteFill : noop)
    ->(removeStroke ? deleteStroke : noop)
    ->template(commonjs)
  );

let transformFiles =
    (files, ~withNative, ~withWeb, ~removeFill, ~removeStroke, ~commonjs) => {
  files->Array.reduce(
    [||],
    (files, file) => {
      let trsf =
        file.content->transformSvg(~removeFill, ~removeStroke, ~commonjs);
      switch (withNative, withWeb) {
      | (false, false) => files
      | (true, false) =>
        files->Array.concat([|
          {
            name: file.name,
            content: trsf(~template=Templates.native, ~pascalCaseTag=true),
          },
        |])
      | (false, true) =>
        files->Array.concat([|
          {
            name: file.name,
            content: trsf(~template=Templates.web, ~pascalCaseTag=false),
          },
        |])
      | (true, true) =>
        files->Array.concat([|
          {
            name: file.name,
            content: trsf(~template=Templates.native, ~pascalCaseTag=true),
          },
          {
            name: file.name ++ ".web",
            content: trsf(~template=Templates.web, ~pascalCaseTag=false),
          },
        |])
      };
    },
  );
};

let write = (outputPath, files) => {
  files->Array.forEach(file => {
    let filename = Path.join([|outputPath, "SVG" ++ file.name ++ ".js"|]);
    mkdirpSync(Path.dirname(filename));
    Fs.writeFileAsUtf8Sync(filename, file.content);
  });
  files;
};

let writeRe = (outputPath, modulePath, files) => {
  files->Array.forEach(file => {
    let filename = file.name;
    let svgJsName = {j|SVG$filename.js|j};
    let svgReName = {j|SVG$filename.re|j};
    let pathname = Path.join([|outputPath, svgReName|]);
    mkdirpSync(Path.dirname(pathname));
    let bsModulePath =
      modulePath
      ->Option.map(path => path->Path.join2(svgJsName))
      // don't use join as path.join(".", "smth") gives "smth"
      ->Option.getWithDefault("." ++ sep ++ svgJsName);

    let reWrapper = {j|
[@react.component] [@bs.module "$bsModulePath"]
external make: (
  ~width: ReactFromSvg.Size.t=?,
  ~height: ReactFromSvg.Size.t=?,
  ~fill: string=?,
  ~stroke: string=?
) => React.element  = "default";
|j};
    Fs.writeFileAsUtf8Sync(pathname, reWrapper);
  });
  files;
};

type flags = {
  withNative: Js.Undefined.t(bool),
  withWeb: Js.Undefined.t(bool),
  withReason: Js.Undefined.t(bool),
  removeFill: Js.Undefined.t(bool),
  removeStroke: Js.Undefined.t(bool),
  commonjs: Js.Undefined.t(bool),
  bsModulePath: Js.Undefined.t(string),
};

let make = ((sourcePath, outputPath), flags) => {
  let futureFiles =
    Path.join([|sourcePath, "*.svg"|])
    ->get
    ->Future.map(files => files->Result.getExn)
    ->Future.tap(files => Js.log2("Files found", files->Array.length))
    ->Future.map(shortenFilenames(sourcePath))
    ->Future.map(files =>
        files->transformFiles(
          ~withNative=
            flags.withNative
            ->Js.Undefined.toOption
            ->Option.getWithDefault(false),
          ~withWeb=
            flags.withWeb
            ->Js.Undefined.toOption
            ->Option.getWithDefault(false),
          ~removeFill=
            flags.removeFill
            ->Js.Undefined.toOption
            ->Option.getWithDefault(false),
          ~removeStroke=
            flags.removeStroke
            ->Js.Undefined.toOption
            ->Option.getWithDefault(false),
          ~commonjs=
            flags.commonjs
            ->Js.Undefined.toOption
            ->Option.getWithDefault(false),
        )
      )
    ->Future.tap(files => Js.log2("Files transformed", files->Array.length))
    ->Future.map(write(outputPath))
    ->Future.tap(files => Js.log2("Files written", files->Array.length));

  if (flags.withReason->Js.Undefined.toOption->Option.getWithDefault(false)) {
    futureFiles
    ->Future.map(
        writeRe(outputPath, flags.bsModulePath->Js.Undefined.toOption),
      )
    ->Future.tap(files =>
        Js.log2("Files written (reason wrappers)", files->Array.length)
      )
    ->ignore;
  };

  futureFiles;
};
