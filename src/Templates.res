type svgOutput = string

let sep = ";\n"
let importReact = commonjs =>
  commonjs ? "const React = require('react')" : "import React from 'react'"
let \"export" = (svgOutput, commonjs) =>
  commonjs
    ? j`module.exports = ({width, height, fill, stroke}) => {
  return ($svgOutput);
}`
    : j`export default ({width, height, fill, stroke}) => {
  return ($svgOutput);
}`

let web = (svgOutput: string, ~commonjs) =>
  importReact(commonjs) ++ (sep ++ (\"export"(svgOutput, commonjs) ++ sep))

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

let native = (svgOutput: string, ~commonjs) =>
  importReact(commonjs) ++
  (sep ++
  (importReactNativeSvg(commonjs) ++ (sep ++ (\"export"(svgOutput, commonjs) ++ sep))))

let nativeForRescript = (svgOutput: string) => {
  let output = {
    open AdjustSvg
    svgOutput->transformReScriptNativeProps->transformReScriptNativeSizeProps
  }
  j`open ReactNative
open ReactNativeSvg

@react.component
let make = (
  ~width: option<Style.size>=?,
  ~height: option<Style.size>=?,
  ~fill: option<string>=?,
  ~stroke: option<string>=?,
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
) => $svgOutput;
`
