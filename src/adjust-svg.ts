import { toCamel, toPascal } from "./case.js";

const tagsToRemove = ["title", "desc"];

const cleanupStart = (svg: string): string => {
  let result = svg
    .replace(/'/g, '"')
    .replace(/\sversion="1.1"/g, "")
    .replace(/<\?xml(.*)\?>/g, "")
    .replace(/\sxmlns="http:\/\/www\.w3\.org\/2000\/svg"/g, "")
    .replace(/\sxmlns:xlink="http:\/\/www.w3.org\/1999\/xlink"/g, "")
    .replace(/<!--(.*)-->/g, "");

  // Remove tags with or without attributes
  tagsToRemove.forEach((tag) => {
    result = result.replace(new RegExp(`<${tag}[^>]*>.*?<\/${tag}>`, "gs"), "");
  });

  return result;
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
  return svg.replace(/\s([a-z][a-z-]+[a-z])/g, (match, p1) => {
    if (p1.startsWith("data-") || p1.startsWith("aria-")) {
      return match;
    }
    return " " + toCamel(p1);
  });
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

const transformStyleAttributes = (svg: string): string => {
  return svg.replace(/ style="([^"]*)"/g, (_, styleContent) => {
    const styleObject = styleContent
      .split(";")
      .filter(Boolean)
      .map((style: string) => {
        const [property, value] = style.split(":").map((s: string) => s.trim());
        return `"${toCamel(property)}": "${value}"`;
      })
      .join(", ");

    return ` style={{${styleObject}}}`;
  });
};

// Replace each existing fill with fill={fills[N]} (N = index of occurrence)
// If fills[N] is strictly undefined, keep the original value unless removeFill is true, then fallback to undefined
function allowOverrideFillWithProp(
  svg: string,
  removeFill: boolean = false,
): string {
  let fillIndex = 0;
  return svg.replace(
    /(<(?!svg)[^\s>]+)([^>]*?)\sfill="([^"]*)"([^>]*>)/g,
    function (
      match: string,
      startTag: string,
      beforeFill: string,
      fillValue: string,
      afterFill: string,
    ) {
      const idx = fillIndex++;
      // If removeFill: no fallback to the original value
      // Otherwise: fallback to the original value
      const fallback = removeFill ? "undefined" : `"${fillValue}"`;
      return `${startTag}${beforeFill} fill={typeof fills !== 'undefined' && typeof fills[${idx}] !== 'undefined' ? fills[${idx}] : ${fallback}}${afterFill}`;
    },
  );
}

export {
  cleanupStart,
  prepareSvgProps,
  injectSvgJsProps,
  dashToCamelCaseProps,
  tagToPascalCase,
  cleanupEndWithoutSpace,
  deleteFill,
  deleteStroke,
  transformStyleAttributes,
  allowOverrideFillWithProp,
};
