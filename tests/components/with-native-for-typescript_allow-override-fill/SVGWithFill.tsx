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
const SVGWithFill = ({
  fills,
  ...props
}: SvgProps & { fills?: (ColorValue | undefined)[] }) => {
  return (
    <Svg viewBox="0 0 30 30" {...props}>
      <G
        fill={
          typeof fills !== "undefined" && typeof fills[0] !== "undefined"
            ? fills[0]
            : "none"
        }
        fillRule="evenodd"
      >
        <Path
          d="m0 0h30v30h-30z"
          fill={
            typeof fills !== "undefined" && typeof fills[1] !== "undefined"
              ? fills[1]
              : "#dd4b39"
          }
        />
        <Path
          d="m10.2955556 11.5277778h-3.39250004l-1.67166667-3.17944447h-2.22888889v3.17944447h-2.99916667v-11.48861113h5.1625c3.04833334 0 4.78555556 1.475 4.78555556 4.03166666 0 1.73722223-.72111111 3.01555556-2.04861111 3.70388889zm-7.2930556-9.09583336v3.52361112h2.17972222c1.21277778 0 1.9175-.62277778 1.9175-1.78638889 0-1.13083334-.70472222-1.73722223-1.9175-1.73722223zm8.8663889-2.39277777h9.0630555v2.39277777h-6.0638888v2.14694445h5.4738888v2.37638889l-5.4738888.01638889v2.16333333h6.2277777v2.3927778h-9.2269444z"
          fill={
            typeof fills !== "undefined" && typeof fills[2] !== "undefined"
              ? fills[2]
              : "#fff"
          }
          fillRule="nonzero"
          transform="translate(7.5 15.833333)"
        />
      </G>
    </Svg>
  );
};

export default SVGWithFill;
