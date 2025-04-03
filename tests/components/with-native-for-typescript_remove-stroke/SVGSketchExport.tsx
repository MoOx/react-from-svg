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
const SVGSketchExport = (props: SvgProps) => {
  return (
    <Svg viewBox="0 0 97 171" {...props}>
      <G id="Page-1" strokeWidth="1" fill="none" fillRule="evenodd">
        <Path
          d="M9.7890625,170.355469 C12.328125,170.355469 14.4765625,169.378906 16.1367188,167.71875 L93.578125,92.0351562 C95.4335938,90.1796875 96.4101562,87.9335938 96.4101562,85.4921875 C96.4101562,82.953125 95.4335938,80.609375 93.578125,78.9492188 L16.234375,3.36328125 C14.4765625,1.60546875 12.328125,0.62890625 9.7890625,0.62890625 C4.7109375,0.62890625 0.90234375,4.53515625 0.90234375,9.61328125 C0.90234375,11.9570312 1.87890625,14.3007813 3.44140625,15.9609375 L74.5351562,85.4921875 L3.44140625,155.023438 C1.87890625,156.683594 0.90234375,158.929688 0.90234375,161.371094 C0.90234375,166.449219 4.7109375,170.355469 9.7890625,170.355469 Z"
          id="chevron"
          fill="#000000"
          fillRule="nonzero"
        ></Path>
      </G>
    </Svg>
  );
};

export default SVGSketchExport;
