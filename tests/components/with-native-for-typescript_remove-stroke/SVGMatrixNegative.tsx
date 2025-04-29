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
const SVGMatrixNegative = (props: SvgProps) => {
  return (
    <Svg viewBox="0 0 288 272" {...props}>
      {props.children}
      <LinearGradient
        id="a"
        x1="19.028507%"
        x2="89.260976%"
        y1="0%"
        y2="73.030917%"
      >
        <Stop offset="0" stopColor="#fecf24" />
        <Stop offset="1" stopColor="#fd12c9" />
      </LinearGradient>
      <LinearGradient
        id="b"
        x1="89.260976%"
        x2="14.927787%"
        y1="69.255008%"
        y2="31.222246%"
      >
        <Stop offset="0" stopColor="#90f0ff" />
        <Stop offset="1" stopColor="#79e3ea" />
      </LinearGradient>
      <Path
        d="m462.778216 3445.9274 220.369072 201.66557-243.031084 72.59684z"
        fill="url(#a)"
        fillRule="evenodd"
        strokeWidth="8.170213"
        transform="matrix(.20791169 .9781476 -.9781476 .20791169 3554.703395 -1163.351461)"
      />
    </Svg>
  );
};

export default SVGMatrixNegative;
