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
        file.name
        |> Js.String.replace(sourcePath ++ "/", "")
        |> Js.String.replace(".svg", ""),
    }
  );
};

let transformSvg = (svg, removeFill) => {
  let transformedSvg =
    svg
    |> Js.String.replaceByRe([%re "/\\sversion=\"1.1\"/g"], "")
    |> Js.String.replaceByRe([%re "/<\\?xml(.*)\\?>/g"], "")
    |> Js.String.replaceByRe(
         [%re "/\\sxmlns=\"http:\\/\\/www\\.w3\\.org\\/2000\\/svg\"/g"],
         "",
       )
    |> Js.String.replaceByRe(
         [%re "/\\sxmlns:xlink=\"http:\\/\\/www.w3.org\\/1999\\/xlink\"/g"],
         "",
       )
    // remove useless data
    |> Js.String.replaceByRe([%re "/<title>(.*)<\\/title>/g"], "")
    |> Js.String.replaceByRe([%re "/<desc>(.*)<\\/desc>/g"], "")
    |> Js.String.replaceByRe([%re "/<!--(.*)-->/g"], "")
    //
    // |> Js.String.replaceByRe([%re "/\"\\//g"], {j|" /|j})
    // add space between jsx element?
    // |> Js.String.replaceByRe([%re "/></g"], {j|> <|j})
    // remove future props
    |> Js.String.replaceByRe(
         [%re "/<svg\\s?(.*)?\\s?width=\"[^\\\"]*\"/g"],
         {j|<svg \$1|j},
       )
    |> Js.String.replaceByRe(
         [%re "/<svg\\s?(.*)?\\s?height=\"[^\\\"]*\"/g"],
         {j|<svg \$1|j},
       )
    |> Js.String.replaceByRe(
         [%re "/<svg\\s?(.*)?\\s?fill=\"[^\\\"]*\"/g"],
         {j|<svg \$1|j},
       )
    // inject props
    |> Js.String.replace(
         ">",
         " width={width} height={height} fill={fill} stroke={stroke}>",
       )
    // case for react-native-svg
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-a([a-z]+)/g"],
         {j| \$1A\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-b([a-z]+)/g"],
         {j| \$1B\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-c([a-z]+)/g"],
         {j| \$1C\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-d([a-z]+)/g"],
         {j| \$1D\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-e([a-z]+)/g"],
         {j| \$1E\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-f([a-z]+)/g"],
         {j| \$1F\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-g([a-z]+)/g"],
         {j| \$1G\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-h([a-z]+)/g"],
         {j| \$1H\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-l([a-z]+)/g"],
         {j| \$1L\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-o([a-z]+)/g"],
         {j| \$1O\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-p([a-z]+)/g"],
         {j| \$1P\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-s([a-z]+)/g"],
         {j| \$1S\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-t([a-z]+)/g"],
         {j| \$1T\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-r([a-z]+)/g"],
         {j| \$1R\$2|j},
       )
    |> Js.String.replaceByRe(
         [%re "/\\s([a-z]+)-w([a-z]+)/g"],
         {j| \$1W\$2|j},
       )
    |> Js.String.replaceByRe([%re "/<(\\/?)a/g"], "<$1A")
    |> Js.String.replaceByRe([%re "/<(\\/?)b/g"], "<$1B")
    |> Js.String.replaceByRe([%re "/<(\\/?)c/g"], "<$1C")
    |> Js.String.replaceByRe([%re "/<(\\/?)d/g"], "<$1D")
    |> Js.String.replaceByRe([%re "/<(\\/?)e/g"], "<$1E")
    |> Js.String.replaceByRe([%re "/<(\\/?)f/g"], "<$1F")
    |> Js.String.replaceByRe([%re "/<(\\/?)g/g"], "<$1G")
    |> Js.String.replaceByRe([%re "/<(\\/?)h/g"], "<$1H")
    |> Js.String.replaceByRe([%re "/<(\\/?)i/g"], "<$1I")
    |> Js.String.replaceByRe([%re "/<(\\/?)j/g"], "<$1J")
    |> Js.String.replaceByRe([%re "/<(\\/?)k/g"], "<$1K")
    |> Js.String.replaceByRe([%re "/<(\\/?)l/g"], "<$1L")
    |> Js.String.replaceByRe([%re "/<(\\/?)m/g"], "<$1M")
    |> Js.String.replaceByRe([%re "/<(\\/?)o/g"], "<$1O")
    |> Js.String.replaceByRe([%re "/<(\\/?)p/g"], "<$1P")
    |> Js.String.replaceByRe([%re "/<(\\/?)q/g"], "<$1Q")
    |> Js.String.replaceByRe([%re "/<(\\/?)r/g"], "<$1R")
    |> Js.String.replaceByRe([%re "/<(\\/?)s/g"], "<$1S")
    |> Js.String.replaceByRe([%re "/<(\\/?)t/g"], "<$1T")
    |> Js.String.replaceByRe([%re "/<(\\/?)u/g"], "<$1U")
    |> Js.String.replaceByRe([%re "/<(\\/?)v/g"], "<$1V")
    |> Js.String.replaceByRe([%re "/<(\\/?)w/g"], "<$1W")
    |> Js.String.replaceByRe([%re "/<(\\/?)x/g"], "<$1X")
    |> Js.String.replaceByRe([%re "/<(\\/?)y/g"], "<$1Y")
    |> Js.String.replaceByRe([%re "/<(\\/?)z/g"], "<$1Z")
    |> Js.String.replaceByRe([%re "/>\\s+</g"], "><");

  let transformedSvgCleaned =
    if (!removeFill) {
      transformedSvg;
    } else {
      transformedSvg
      |> Js.String.replaceByRe([%re "/ fill=\"[^\\\"]*\"/g"], "");
    };
  Some(
    {j|import React from 'react';
import Svg, {
  Circle,
  Ellipse,
  G,
  Text,
  TSpan as Tspan,
  TextPath,
  Path,
  Polygon,
  Polyline,
  Line,
  Rect,
  Use,
  Image,
  Symbol,
  Defs,
  LinearGradient,
  RadialGradient,
  Stop,
  ClipPath,
  Pattern,
  Mask,
} from 'react-native-svg';

export default ({width, height, fill, stroke}) => {
  return (
$transformedSvgCleaned
  );
};
|j},
  );
};

let transform = (files, removeFill) => {
  let f =
    files->Array.reduce([||], (files, file) =>
      file.content
      ->transformSvg(removeFill)
      ->Option.map(content => files->Array.concat([|{...file, content}|]))
      ->Option.getWithDefault(files)
    );

  f;
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

let make = (sourcePath, outputPath, reason, removeFill, modulePath) => {
  let futureFiles =
    Path.join([|sourcePath, "*.svg"|])
    ->get
    ->Future.map(files => files->Result.getExn)
    ->Future.tap(files => Js.log2("Files found", files->Array.length))
    ->Future.map(shortenFilenames(sourcePath))
    ->Future.map(files => transform(files, removeFill))
    ->Future.tap(files => Js.log2("Files transformed", files->Array.length))
    ->Future.map(write(outputPath))
    ->Future.tap(files => Js.log2("Files written", files->Array.length));

  if (reason) {
    futureFiles
    ->Future.map(writeRe(outputPath, Js.Nullable.toOption(modulePath)))
    ->Future.tap(files =>
        Js.log2("Files written (reason wrappers)", files->Array.length)
      )
    ->ignore;
  };

  futureFiles;
};
