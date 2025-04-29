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
const SVGSimple = ({
  fills,
  ...props
}: SvgProps & { fills?: (ColorValue | undefined)[] }) => {
  return (
    <Svg viewBox="0 0 512 512" {...props}>
      <Path
        d="M336 192h40a40 40 0 0140 40v192a40 40 0 01-40 40H136a40 40 0 01-40-40V232a40 40 0 0140-40h40M336 128l-80-80-80 80M256 321V48"
        fill={
          typeof fills !== "undefined" && typeof fills[0] !== "undefined"
            ? fills[0]
            : "none"
        }
        stroke="#000"
        strokeLinecap="round"
        strokeLinejoin="round"
        strokeWidth="32"
        opacity="0.1"
      />
    </Svg>
  );
};

export default SVGSimple;
