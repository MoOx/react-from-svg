open Node
open Belt

@module("mkdirp") external mkdirpSync: string => unit = "sync"

let root = Process.cwd()
let sep = Path.sep

type file = {
  name: string,
  content: string,
}

let get = (globPattern: string) =>
  globPattern
  ->Glob.glob
  ->Future.mapOk(SortArray.String.stableSort)
  ->Future.mapOk(Array.reverse)
  ->Future.mapOk(files =>
    files->Array.map(item => {name: item, content: Fs.readFileAsUtf8Sync(item)})
  )

let shortenFilenames = (sourcePath, files) =>
  files->Array.map(file => {
    ...file,
    name: (file.name |> Js.String.replace(sourcePath ++ "/", "") |> Js.String.replace(".svg", ""))
      ->Case.toPascal,
  })

let noop = s => s

let transformSvg = (svg, ~removeFill, ~removeStroke, ~pascalCaseTag, ~js, ~template) => {
  open AdjustSvg
  svg
  ->cleanupStart
  ->prepareSvgProps
  ->(js ? injectSvgJsProps : injectSvgReScriptProps)
  ->dashToCamelCaseProps
  ->(pascalCaseTag ? tagToPascalCase : noop)
  ->(js ? cleanupEndWithoutSpace : cleanupEndWithSpace)
  ->(removeFill ? deleteFill : noop)
  ->(removeStroke ? deleteStroke : noop)
  ->template
}

let makeName = name => "SVG" ++ name

let transformFiles = (
  files,
  ~withNative,
  ~withNativeForTypescript: bool,
  ~withWeb,
  ~withNativeForRescript,
  ~withWebForRescript,
  ~removeFill,
  ~removeStroke,
  ~commonjs,
) =>
  files->Array.reduce([], (files, file) => {
    let name = makeName(file.name)
    let trsf = file.content->transformSvg(~removeFill, ~removeStroke)
    let trsfNative = () =>
      trsf(~js=true, ~pascalCaseTag=true, ~template=Templates.native(~commonjs, ~name))
    let trsfNativeForTs = () =>
      trsf(~js=true, ~pascalCaseTag=true, ~template=Templates.nativeForTypescript(~commonjs, ~name))
    let trsfWeb = () =>
      trsf(~js=true, ~pascalCaseTag=false, ~template=Templates.web(~commonjs, ~name))
    let trsfNativeForR = () =>
      trsf(~js=false, ~pascalCaseTag=true, ~template=Templates.nativeForRescript)
    let trsfWebForR = () =>
      trsf(~js=false, ~pascalCaseTag=false, ~template=Templates.webForRescript)
    switch (
      withNative,
      withNativeForTypescript,
      withWeb,
      withNativeForRescript,
      withWebForRescript,
    ) {
    | (false, false, false, false, false) => files
    | (true, false, false, false, false) =>
      files->Array.concat([{name: file.name ++ ".js", content: trsfNative()}])
    | (true, true, false, false, false) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfNative()},
        {name: file.name ++ ".tsx", content: trsfNativeForTs()},
      ])
    | (false, false, true, false, false) =>
      files->Array.concat([{name: file.name ++ ".js", content: trsfWeb()}])
    | (false, true, false, false, false) =>
      files->Array.concat([{name: file.name ++ ".tsx", content: trsfNativeForTs()}])
    | (false, true, true, false, false) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfWeb()},
        {name: file.name ++ ".tsx", content: trsfNativeForTs()},
      ])
    | (true, false, true, false, false) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfNative()},
        {name: file.name ++ ".web.js", content: trsfWeb()},
      ])
    | (true, true, true, false, false) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfNative()},
        {name: file.name ++ ".tsx", content: trsfNativeForTs()},
        {name: file.name ++ ".web.js", content: trsfWeb()},
      ])
    | (false, false, false, true, false) =>
      files->Array.concat([{name: file.name ++ ".res", content: trsfNativeForR()}])
    | (false, true, false, true, false) =>
      files->Array.concat([
        {name: file.name ++ ".tsx", content: trsfNativeForTs()},
        {name: file.name ++ ".res", content: trsfNativeForR()},
      ])
    | (false, false, false, false, true) =>
      files->Array.concat([{name: file.name ++ ".res", content: trsfWebForR()}])
    | (false, true, false, false, true) =>
      files->Array.concat([
        {name: file.name ++ ".tsx", content: trsfNativeForTs()},
        {name: file.name ++ ".res", content: trsfWebForR()},
      ])
    | (true, false, true, true, false) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfNative()},
        {name: file.name ++ ".web.js", content: trsfWeb()},
        {name: file.name ++ ".res", content: trsfNativeForR()},
      ])
    | (true, true, true, true, false) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfNative()},
        {name: file.name ++ ".tsx", content: trsfNativeForTs()},
        {name: file.name ++ ".web.js", content: trsfWeb()},
        {name: file.name ++ ".res", content: trsfNativeForR()},
      ])
    | (true, false, true, false, true) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfNative()},
        {name: file.name ++ ".web.js", content: trsfWeb()},
        {name: file.name ++ ".res", content: trsfWebForR()},
      ])
    | (true, true, true, false, true) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfNative()},
        {name: file.name ++ ".tsx", content: trsfNativeForTs()},
        {name: file.name ++ ".web.js", content: trsfWeb()},
        {name: file.name ++ ".res", content: trsfWebForR()},
      ])
    | (true, false, false, true, false) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfNative()},
        {name: file.name ++ ".res", content: trsfNativeForR()},
      ])
    | (true, true, false, true, false) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfNative()},
        {name: file.name ++ ".tsx", content: trsfNativeForTs()},
        {name: file.name ++ ".res", content: trsfNativeForR()},
      ])
    | (true, false, false, false, true) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfNative()},
        {name: file.name ++ ".res", content: trsfWebForR()},
      ])
    | (true, true, false, false, true) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfNative()},
        {name: file.name ++ ".tsx", content: trsfNativeForTs()},
        {name: file.name ++ ".res", content: trsfWebForR()},
      ])
    | (false, false, true, true, false) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfWeb()},
        {name: file.name ++ ".res", content: trsfNativeForR()},
      ])
    | (false, true, true, true, false) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfWeb()},
        {name: file.name ++ ".tsx", content: trsfNativeForTs()},
        {name: file.name ++ ".res", content: trsfNativeForR()},
      ])
    | (false, false, true, false, true) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfWeb()},
        {name: file.name ++ ".res", content: trsfWebForR()},
      ])
    | (false, true, true, false, true) =>
      files->Array.concat([
        {name: file.name ++ ".js", content: trsfWeb()},
        {name: file.name ++ ".tsx", content: trsfNativeForTs()},
        {name: file.name ++ ".res", content: trsfWebForR()},
      ])
    | (_, _, _, true, true) =>
      failwith(
        "For now --with-native-for-rescript & --with-web-for-rescript cannot be used at the same time.",
      )
    }
  })

let write = (outputPath, files) => {
  files->Array.forEach(file => {
    let filename = Path.join([outputPath, makeName(file.name)])
    mkdirpSync(Path.dirname(filename))
    Fs.writeFileAsUtf8Sync(filename, file.content)
  })
  files
}

type flags = {
  withNative: Js.Undefined.t<bool>,
  withNativeForTypescript: Js.Undefined.t<bool>,
  withWeb: Js.Undefined.t<bool>,
  withNativeForRescript: Js.Undefined.t<bool>,
  withWebForRescript: Js.Undefined.t<bool>,
  removeFill: Js.Undefined.t<bool>,
  removeStroke: Js.Undefined.t<bool>,
  commonjs: Js.Undefined.t<bool>,
}

let make = ((sourcePath, outputPath), flags) => {
  let futureFiles =
    Path.join([sourcePath, "*.svg"])
    ->get
    ->Future.map(files => files->Result.getExn)
    ->Future.tap(files => Js.log2("Files found", files->Array.length))
    ->Future.map(shortenFilenames(sourcePath))
    ->Future.map(files =>
      files->transformFiles(
        ~withNative=flags.withNative->Js.Undefined.toOption->Option.getWithDefault(false),
        ~withNativeForTypescript=flags.withNativeForTypescript
        ->Js.Undefined.toOption
        ->Option.getWithDefault(false),
        ~withWeb=flags.withWeb->Js.Undefined.toOption->Option.getWithDefault(false),
        ~withNativeForRescript=flags.withNativeForRescript
        ->Js.Undefined.toOption
        ->Option.getWithDefault(false),
        ~withWebForRescript=flags.withWebForRescript
        ->Js.Undefined.toOption
        ->Option.getWithDefault(false),
        ~removeFill=flags.removeFill->Js.Undefined.toOption->Option.getWithDefault(false),
        ~removeStroke=flags.removeStroke->Js.Undefined.toOption->Option.getWithDefault(false),
        ~commonjs=flags.commonjs->Js.Undefined.toOption->Option.getWithDefault(false),
      )
    )
    ->Future.tap(files => Js.log2("Files transformed", files->Array.length))
    ->Future.map(write(outputPath))
    ->Future.tap(files => Js.log2("Files written", files->Array.length))

  futureFiles
}
