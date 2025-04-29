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
const SVGWithStyleAndData = ({
  fills,
  ...props
}: SvgProps & { fills?: (ColorValue | undefined)[] }) => {
  return (
    <Svg {...props}>
      <Mask style={{ maskType: "alpha" }} />
      <Circle
        cx="90"
        cy="90"
        data-circle="true"
        fill={
          typeof fills !== "undefined" && typeof fills[0] !== "undefined"
            ? fills[0]
            : undefined
        }
      />
    </Svg>
  );
};

export default SVGWithStyleAndData;
