open Node;
open Belt;

[@bs.module "mkdirp"] external mkdirpSync: string => unit = "sync";

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
        ->Case.toPascal,
    }
  );
};

let noop = s => s;

let transformSvg =
    (svg, ~removeFill, ~removeStroke, ~pascalCaseTag, ~js, ~template) =>
  AdjustSvg.(
    svg
    ->cleanupStart
    ->prepareSvgProps
    ->(js ? injectSvgJsProps : injectSvgReasonProps)
    ->dashToCamelCaseProps
    ->(pascalCaseTag ? tagToPascalCase : noop)
    ->cleanupEnd
    ->(removeFill ? deleteFill : noop)
    ->(removeStroke ? deleteStroke : noop)
    ->template
  );

let transformFiles =
    (
      files,
      ~withNative,
      ~withWeb,
      ~withNativeForReason,
      ~withWebForReason,
      ~removeFill,
      ~removeStroke,
      ~commonjs,
    ) => {
  files->Array.reduce(
    [||],
    (files, file) => {
      let trsf = file.content->transformSvg(~removeFill, ~removeStroke);
      let trsfNative = () =>
        trsf(
          ~js=true,
          ~pascalCaseTag=true,
          ~template=Templates.native(~commonjs),
        );
      let trsfWeb = () =>
        trsf(
          ~js=true,
          ~pascalCaseTag=false,
          ~template=Templates.web(~commonjs),
        );
      let trsfNativeForR = () =>
        trsf(
          ~js=false,
          ~pascalCaseTag=true,
          ~template=Templates.nativeForReason,
        );
      let trsfWebForR = () =>
        trsf(
          ~js=false,
          ~pascalCaseTag=false,
          ~template=Templates.webForReason,
        );
      switch (withNative, withWeb, withNativeForReason, withWebForReason) {
      | (false, false, false, false) => files
      | (true, false, false, false) =>
        files->Array.concat([|
          {name: file.name ++ ".js", content: trsfNative()},
        |])
      | (false, true, false, false) =>
        files->Array.concat([|
          {name: file.name ++ ".js", content: trsfWeb()},
        |])
      | (true, true, false, false) =>
        files->Array.concat([|
          {name: file.name ++ ".js", content: trsfNative()},
          {name: file.name ++ ".web.js", content: trsfWeb()},
        |])
      | (false, false, true, false) =>
        files->Array.concat([|
          {name: file.name ++ ".re", content: trsfNativeForR()},
        |])
      | (false, false, false, true) =>
        files->Array.concat([|
          {name: file.name ++ ".re", content: trsfWebForR()},
        |])
      | (true, true, true, false) =>
        files->Array.concat([|
          {name: file.name ++ ".js", content: trsfNative()},
          {name: file.name ++ ".web.js", content: trsfWeb()},
          {name: file.name ++ ".re", content: trsfNativeForR()},
        |])
      | (true, true, false, true) =>
        files->Array.concat([|
          {name: file.name ++ ".js", content: trsfNative()},
          {name: file.name ++ ".web.js", content: trsfWeb()},
          {name: file.name ++ ".re", content: trsfWebForR()},
        |])
      | (true, false, true, false) =>
        files->Array.concat([|
          {name: file.name ++ ".js", content: trsfNative()},
          {name: file.name ++ ".re", content: trsfNativeForR()},
        |])
      | (true, false, false, true) =>
        files->Array.concat([|
          {name: file.name ++ ".js", content: trsfNative()},
          {name: file.name ++ ".re", content: trsfWebForR()},
        |])
      | (false, true, true, false) =>
        files->Array.concat([|
          {name: file.name ++ ".js", content: trsfWeb()},
          {name: file.name ++ ".re", content: trsfNativeForR()},
        |])
      | (false, true, false, true) =>
        files->Array.concat([|
          {name: file.name ++ ".js", content: trsfWeb()},
          {name: file.name ++ ".re", content: trsfWebForR()},
        |])
      | (_, _, true, true) =>
        failwith(
          "For now --with-native-for-reason & --with-web-for-reason cannot be used at the same time.",
        )
      };
    },
  );
};

let write = (outputPath, files) => {
  files->Array.forEach(file => {
    let filename = Path.join([|outputPath, "SVG" ++ file.name|]);
    mkdirpSync(Path.dirname(filename));
    Fs.writeFileAsUtf8Sync(filename, file.content);
  });
  files;
};

type flags = {
  withNative: Js.Undefined.t(bool),
  withWeb: Js.Undefined.t(bool),
  withNativeForReason: Js.Undefined.t(bool),
  withWebForReason: Js.Undefined.t(bool),
  removeFill: Js.Undefined.t(bool),
  removeStroke: Js.Undefined.t(bool),
  commonjs: Js.Undefined.t(bool),
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
          ~withNativeForReason=
            flags.withNativeForReason
            ->Js.Undefined.toOption
            ->Option.getWithDefault(false),
          ~withWebForReason=
            flags.withWebForReason
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

  futureFiles;
};
