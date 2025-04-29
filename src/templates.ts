const sep = ";\n";

// Helper for prop signature
function getPropsSignature(
  allowOverrideFill: boolean,
  typescript: boolean,
  native: boolean,
): string {
  const fillsType = `{fills?: (${native ? "ColorValue" : "string"} | undefined)[]}`;
  const optionalPropsType = typescript
    ? ` : ${
        native ? "SvgProps" : "React.SVGProps<SVGSVGElement>"
      }${allowOverrideFill ? " & " + fillsType : ""}`
    : "";
  return `(${allowOverrideFill ? "{ fills, ...props }" : "props"}${optionalPropsType})`;
}

const importReact = (): string => {
  return "import React from 'react'";
};

const jsExport = (
  name: string,
  svgOutput: string,
  allowOverrideFill: boolean = false,
): string => {
  const content =
    `const ${name} = ${getPropsSignature(allowOverrideFill, false, false)} => {
  return (${svgOutput});
}` + sep;
  return `${content}
export default ${name}`;
};

const tsxExport = (
  name: string,
  svgOutput: string,
  native: boolean,
  allowOverrideFill: boolean = false,
): string => {
  const content =
    `const ${name} = ${getPropsSignature(allowOverrideFill, true, native)} => {
  return (${svgOutput});
}` + sep;
  return `${content}
export default ${name}`;
};

const web = (
  svgOutput: string,
  name: string,
  allowOverrideFill: boolean = false,
): string => {
  return (
    importReact() + sep + jsExport(name, svgOutput, allowOverrideFill) + sep
  );
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

const importReactNativeSvg = (
  typescript: boolean,
  allowOverrideFill: boolean,
): string => {
  return `import Svg, {
  ${RNSvgModules.join(",")}
} from 'react-native-svg';${
    typescript && allowOverrideFill
      ? `import type { ColorValue } from 'react-native';`
      : ""
  }${typescript ? `import type { SvgProps } from 'react-native-svg';` : ""}
`;
};

const native = (
  svgOutput: string,
  name: string,
  allowOverrideFill: boolean = false,
): string => {
  return (
    importReact() +
    sep +
    importReactNativeSvg(false, allowOverrideFill) +
    sep +
    jsExport(name, svgOutput, allowOverrideFill) +
    sep
  );
};

const nativeForTypescript = (
  svgOutput: string,
  name: string,
  allowOverrideFill: boolean = false,
): string => {
  return (
    importReact() +
    sep +
    importReactNativeSvg(true, allowOverrideFill) +
    sep +
    tsxExport(name, svgOutput, true, allowOverrideFill) +
    sep
  );
};

const webForTypescript = (
  svgOutput: string,
  name: string,
  allowOverrideFill: boolean = false,
): string => {
  return (
    importReact() +
    sep +
    tsxExport(name, svgOutput, false, allowOverrideFill) +
    sep
  );
};

export { web, native, nativeForTypescript, webForTypescript };
