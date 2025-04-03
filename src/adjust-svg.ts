import { toCamel, toPascal } from "./case.js";

const cleanupStart = (svg: string): string => {
  return svg
    .replace(/'/g, '"')
    .replace(/\sversion="1.1"/g, "")
    .replace(/<\?xml(.*)\?>/g, "")
    .replace(/\sxmlns="http:\/\/www\.w3\.org\/2000\/svg"/g, "")
    .replace(/\sxmlns:xlink="http:\/\/www.w3.org\/1999\/xlink"/g, "")
    .replace(/<title>(.*)<\/title>/g, "")
    .replace(/<desc>(.*)<\/desc>/g, "")
    .replace(/<!--(.*)-->/g, "");
};

const prepareSvgProps = (svg: string): string => {
  return svg
    .replace(/<svg\s?([^>]*)?\swidth="[^"]*"/g, "<svg $1")
    .replace(/<svg\s?([^>]*)?\sheight="[^"]*"/g, "<svg $1")
    .replace(/<svg\s?([^>]*)?\sfill="[^"]*"/g, "<svg $1");
};

const injectSvgJsProps = (svg: string): string => {
  return svg.replace(">", " {...props}>");
};

const dashToCamelCaseProps = (svg: string): string => {
  return svg.replace(/\s([a-z-]+)/g, (_, p1) => " " + toCamel(p1));
};

const tagToPascalCase = (svg: string): string => {
  return svg.replace(
    /<(\/?)([a-z])/g,
    (_, p1, p2) => "<" + (p1 + toPascal(p2)),
  );
};

const cleanupEndWithoutSpace = (svg: string): string => {
  return svg.replace(/>\s+</g, "><");
};

const deleteFill = (svg: string): string => {
  return svg.replace(/ fill="[^"]*"/g, "");
};

const deleteStroke = (svg: string): string => {
  return svg.replace(/ stroke="[^"]*"/g, "");
};

const toPolyCamel = (s: string, re: RegExp): string => {
  return s.replace(re, (_, p1, p2) => p1 + ("=#" + toCamel(p2)));
};

export {
  cleanupStart,
  prepareSvgProps,
  injectSvgJsProps,
  dashToCamelCaseProps,
  tagToPascalCase,
  cleanupEndWithoutSpace,
  deleteFill,
  deleteStroke,
};
