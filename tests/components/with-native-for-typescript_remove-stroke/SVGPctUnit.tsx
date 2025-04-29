import React from "react";
import Svg, {
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
} from "react-native-svg";
import type { SvgProps } from "react-native-svg";
const SVGPctUnit = (props: SvgProps) => {
  return (
    <Svg {...props}>
      {props.children}
      <Circle cx="2%" cy="-4.0%" />
    </Svg>
  );
};

export default SVGPctUnit;
