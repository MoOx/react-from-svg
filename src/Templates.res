type svgOutput = string

let sep = ";\n"
let importReact = commonjs =>
  commonjs ? "const React = require('react')" : "import React from 'react'"
let jsExport = (name, svgOutput, commonjs) =>
  commonjs
    ? j`const $name = ({width, height, fill, stroke, style}) => {
  return ($svgOutput);
};
module.exports =$name`
    : j`const $name = ({width, height, fill, stroke, style}) => {
  return ($svgOutput);
};
export default $name`
let tsxExport = (name, svgOutput, commonjs) =>
  commonjs
    ? j`const $name = ({width, height, fill, stroke, style}: ReactFromSVGProps) => {
  return ($svgOutput);
};
module.exports =$name`
    : j`const $name = ({width, height, fill, stroke, style}: ReactFromSVGProps) => {
  return ($svgOutput);
};
export default $name`

let web = (svgOutput: string, ~commonjs, ~name: string) =>
  importReact(commonjs) ++ (sep ++ (jsExport(name, svgOutput, commonjs) ++ sep))

let importReactNativeSvg = commonjs =>
  commonjs
    ? j`const {
  default as Svg,
  Circle,
  ClipPath,
  Defs,
  Ellipse,
  ForeignObject,
  G,
  Image,
  Line,
  LinearGradient,
  Marker,
  Mask,
  Path,
  Pattern,
  Polygon,
  Polyline,
  RadialGradient,
  Rect,
  Stop,
  Symbol,
  Text,
  TextPath,
  TSpan as Tspan,
  Use,
} = require('react-native-svg')`
    : j`import Svg, {
  Circle,
  ClipPath,
  Defs,
  Ellipse,
  ForeignObject,
  G,
  Image,
  Line,
  LinearGradient,
  Marker,
  Mask,
  Path,
  Pattern,
  Polygon,
  Polyline,
  RadialGradient,
  Rect,
  Stop,
  Symbol,
  Text,
  TextPath,
  TSpan as Tspan,
  Use,
} from 'react-native-svg'`

let native = (svgOutput: string, ~commonjs, ~name: string) =>
  importReact(commonjs) ++
  (sep ++
  (importReactNativeSvg(commonjs) ++ (sep ++ (jsExport(name, svgOutput, commonjs) ++ sep))))

let nativeForTypescript = (svgOutput: string, ~commonjs, ~name: string) =>
  importReact(commonjs) ++
  (sep ++
  (importReactNativeSvg(commonjs) ++
  j`
type ReactFromSVGProps = {
  width?: number;
  height?: number;
  fill?: string;
  stroke?: string;
  style?: any;
};` ++
  (sep ++
  (tsxExport(name, svgOutput, commonjs) ++ sep))))

let nativeForRescript = (svgOutput: string) => {
  let output = {
    open AdjustSvg
    svgOutput
    ->transformReScriptNativeProps
    ->transformReScriptNativeSizeProps
    ->transformReScriptNativeMatrixProps
    ->transformReScriptNativeFixupDigits
  }
  j`open ReactNative
open ReactNativeSvg

@react.component
let make = (
  ~width: option<Style.size>=?,
  ~height: option<Style.size>=?,
  ~fill: option<string>=?,
  ~stroke: option<string>=?,
  ~style: option<Style.t>=?,
) =>$output;
`
}

let webForRescript = (svgOutput: string) =>
  j`@react.component
let make = (
  ~width: option<string>=?,
  ~height: option<string>=?,
  ~fill: option<string>=?,
  ~stroke: option<string>=?,
  ~style: option<Style.t>=?,
) => $svgOutput;
`
