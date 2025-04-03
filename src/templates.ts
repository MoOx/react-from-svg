const sep = ";\n";

const importReact = (): string => {
  return "import React from 'react'";
};

const jsExport = (name: string, svgOutput: string): string => {
  const content =
    `const ${name} = (props) => {
  return (${svgOutput});
}` + sep;
  return `${content}
export default ${name}`;
};

const tsxExport = (
  name: string,
  svgOutput: string,
  native: boolean,
): string => {
  const content =
    `const ${name} = (props: ${
      native ? "SvgProps" : "React.SVGProps<SVGSVGElement>"
    }) => {
  return (${svgOutput});
}` + sep;
  return `${content}
export default ${name}`;
};

const web = (svgOutput: string, name: string): string => {
  return importReact() + sep + jsExport(name, svgOutput) + sep;
};

const RNSvgModules = [
  "Circle",
  "ClipPath",
  "Defs",
  "Ellipse",
  "ForeignObject",
  "G",
  "Image",
  "Line",
  "LinearGradient",
  "Marker",
  "Mask",
  "Path",
  "Pattern",
  "Polygon",
  "Polyline",
  "RadialGradient",
  "Rect",
  "Stop",
  "Symbol",
  "Text",
  "TextPath",
  "TSpan as Tspan",
  "Use",
];

const importReactNativeSvg = (typescript: boolean): string => {
  return `import Svg, {
  ${RNSvgModules.join(",")}
} from 'react-native-svg'
${typescript ? "import type { SvgProps } from 'react-native-svg'" : ""}`;
};

const native = (svgOutput: string, name: string): string => {
  return (
    importReact() +
    sep +
    importReactNativeSvg(false) +
    sep +
    jsExport(name, svgOutput) +
    sep
  );
};

const nativeForTypescript = (svgOutput: string, name: string): string => {
  return (
    importReact() +
    sep +
    importReactNativeSvg(true) +
    sep +
    tsxExport(name, svgOutput, true) +
    sep
  );
};

const webForTypescript = (svgOutput: string, name: string): string => {
  return importReact() + sep + tsxExport(name, svgOutput, false) + sep;
};

export { web, native, nativeForTypescript, webForTypescript };
