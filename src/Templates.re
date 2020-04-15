type svgOutput = string;

let sep = ";\n";
let importReact = commonjs =>
  commonjs ? "const React = require('react')" : "import React from 'react'";
let export = (svgOutput, commonjs) =>
  commonjs
    ? {j|module.exports = ({width, height, fill, stroke}) => {
  return ($svgOutput);
}|j}
    : {j|export default ({width, height, fill, stroke}) => {
  return ($svgOutput);
}|j};

let web = (svgOutput: string, ~commonjs) =>
  importReact(commonjs) ++ sep ++ export(svgOutput, commonjs) ++ sep;

let importReactNativeSvg = commonjs =>
  commonjs
    ? {j|const {
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
  Symbol,
  Text,
  TextPath,
  TSpan as Tspan,
  Use,
} = require('react-native-svg')|j}
    : {j|import Svg, {
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
  Symbol,
  Text,
  TextPath,
  TSpan as Tspan,
  Use,
} from 'react-native-svg'|j};

let native = (svgOutput: string, ~commonjs) =>
  importReact(commonjs)
  ++ sep
  ++ importReactNativeSvg(commonjs)
  ++ sep
  ++ export(svgOutput, commonjs)
  ++ sep;

let nativeForReason = (svgOutput: string) => {
  let output =
    AdjustSvg.(
      svgOutput->transformReasonNativeProps->transformReasonNativeSizeProps
    );
  {j|open ReactNative.Style;
open ReactNativeSvg;

[@react.component]
let make =
    (
      ~width: option(size)=?,
      ~height: option(size)=?,
      ~fill: option(string)=?,
      ~stroke: option(string)=?,
    ) => $output;
|j};
};

let webForReason = (svgOutput: string) => {j|[@react.component]
let make =
    (
      ~width: option(string)=?,
      ~height: option(string)=?,
      ~fill: option(string)=?,
      ~stroke: option(string)=?,
    ) => $svgOutput;
|j};
