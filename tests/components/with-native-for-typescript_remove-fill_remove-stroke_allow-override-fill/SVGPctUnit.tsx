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
import type { ColorValue } from "react-native";
import type { SvgProps } from "react-native-svg";
const SVGPctUnit = ({
  fills,
  ...props
}: SvgProps & { fills?: (ColorValue | undefined)[] }) => {
  return (
    <Svg {...props}>
      <Circle cx="2%" cy="-4.0%" />
    </Svg>
  );
};

export default SVGPctUnit;
