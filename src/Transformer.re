open Node;
open Belt;

[@bs.module "mkdirp"] external mkdirpSync: string => unit = "sync";

let root = Process.cwd();

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
        file.name
        |> Js.String.replace(sourcePath ++ "/", "")
        |> Js.String.replace(".svg", ""),
    }
  );
};

// web only for now
let transformSvg = svg => {
  let transformedSvg =
    svg
    |> Js.String.replaceByRe(
         [%re "/\sxmlns\=\"http:\/\/www\.w3\.org\/2000\/svg\"/g"],
         "",
       )
    |> Js.String.replaceByRe(
         [%re "/\sxmlns:xlink\=\"http:\/\/www.w3.org\/1999\/xlink\"/g"],
         "",
       )
    |> Js.String.replaceByRe([%re "/\sfill-rule=\"/g"], {j| fillRule="|j})
    |> Js.String.replaceByRe([%re "/\"\//g"], {j|" /|j})
    |> Js.String.replaceByRe([%re "/></g"], {j|> <|j})
    // remove future props
    |> Js.String.replaceByRe(
         [%re "/<svg\s?(.*)?\s?width=\"[^\\\"]*\"/g"],
         {j|<svg \$1|j},
       )
    |> Js.String.replaceByRe(
         [%re "/<svg\s?(.*)?\s?height=\"[^\\\"]*\"/g"],
         {j|<svg \$1|j},
       )
    |> Js.String.replaceByRe(
         [%re "/<svg\s?(.*)?\s?fill=\"[^\\\"]*\"/g"],
         {j|<svg \$1|j},
       )
    // inject props
    |> Js.String.replace(">", "?width ?height ?fill>");

  Some(
    {j|
[@react.component]
let make =
  (
    ~width: option(ReactFromSvg.Size.t)=?,
    ~height: option(ReactFromSvg.Size.t)=?,
    ~fill: option(ReactFromSvg.Size.t)=?
  ) => {
$transformedSvg
  };
|j},
  );
};

let transform = files => {
  let f =
    files->Array.reduce([||], (files, file) =>
      file.content
      ->transformSvg
      ->Option.map(content => files->Array.concat([|{...file, content}|]))
      ->Option.getWithDefault(files)
    );

  f;
};

let write = (outputPath, files) => {
  files->Array.forEach(file => {
    let filename = Path.join([|outputPath, "SVG" ++ file.name ++ ".re"|]);
    mkdirpSync(Path.dirname(filename));
    Fs.writeFileAsUtf8Sync(filename, file.content);
  });
  files;
};

let make = (sourcePath, outputPath) => {
  Path.join([|sourcePath, "*.svg"|])
  ->get
  ->Future.map(files => files->Result.getExn)
  ->Future.tap(files => Js.log2("Files found", files->Array.length))
  ->Future.map(shortenFilenames(sourcePath))
  ->Future.map(transform)
  ->Future.tap(files => Js.log2("Files transformed", files->Array.length))
  ->Future.map(write(outputPath))
  ->Future.tap(files => Js.log2("Files written", files->Array.length));
};
