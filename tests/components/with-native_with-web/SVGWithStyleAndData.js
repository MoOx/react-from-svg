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
const SVGWithStyleAndData = (props) => {
  return (
    <Svg {...props}>
      <Mask style={{ maskType: "alpha" }} />
      <Circle cx="90" cy="90" data-circle="true" fill="black" />
    </Svg>
  );
};

export default SVGWithStyleAndData;
