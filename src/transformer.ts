import { mkdirp } from "mkdirp";
import { join, dirname } from "node:path";
import { readFileSync, writeFileSync } from "node:fs";
import { glob } from "glob";
import { toPascal } from "./case.js";
import {
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
} from "./adjust-svg.js";
import {
  web,
  native,
  nativeForTypescript,
  webForTypescript,
} from "./templates.js";

type File = {
  name: string;
  content: string;
};

type Flags = {
  withNative?: boolean;
  withNativeForTypescript?: boolean;
  withWeb?: boolean;
  withWebForTypescript?: boolean;
  removeFill?: boolean;
  removeStroke?: boolean;
  allowOverrideFill?: boolean;
};

const get = async (globPattern: string): Promise<File[]> => {
  const files = await glob(globPattern.replace(/\\/g, '/'), { posix: true });
  return files
    .sort()
    .reverse()
    .map((item: string) => ({
      name: item,
      content: readFileSync(item, "utf8"),
    }));
};

const shortenFilenames = (sourcePath: string, files: File[]): File[] => {
  return files.map((file) => ({
    ...file,
    name: file.name
      .replace(sourcePath + "/", "")
      .replace(".svg", "")
      .split("/")
      .map((part) => toPascal(part))
      .join("/"),
  }));
};

export const transformSvg = (
  svg: string,
  options: {
    removeFill: boolean;
    removeStroke: boolean;
    allowOverrideFill: boolean;
    pascalCaseTag: boolean;
    template: (svg: string) => string;
  },
): string => {
  const {
    removeFill,
    removeStroke,
    allowOverrideFill,
    pascalCaseTag,
    template,
  } = options;

  let result = cleanupStart(svg);
  result = prepareSvgProps(result);
  result = injectSvgJsProps(result);
  result = dashToCamelCaseProps(result);
  result = transformStyleAttributes(result);
  result = pascalCaseTag ? tagToPascalCase(result) : result;
  result = cleanupEndWithoutSpace(result);
  if (allowOverrideFill) {
    result = allowOverrideFillWithProp(result, removeFill);
  }
  result = removeFill ? deleteFill(result) : result;
  result = removeStroke ? deleteStroke(result) : result;

  return template(result);
};

const makeName = (name: string): string => "SVG" + name;

const transformFiles = (
  files: File[],
  options: {
    withNative: boolean;
    withNativeForTypescript: boolean;
    withWeb: boolean;
    withWebForTypescript: boolean;
    removeFill: boolean;
    removeStroke: boolean;
    allowOverrideFill: boolean;
  },
): File[] => {
  const {
    withNative,
    withNativeForTypescript,
    withWeb,
    withWebForTypescript,
    removeFill,
    removeStroke,
    allowOverrideFill,
  } = options;

  return files.reduce((acc, file) => {
    const name = makeName(file.name);
    const trsf = (options: {
      js: boolean;
      pascalCaseTag: boolean;
      template: (svg: string) => string;
    }) =>
      transformSvg(file.content, {
        removeFill,
        removeStroke,
        allowOverrideFill,
        ...options,
      });

    const trsfNative = () =>
      trsf({
        js: true,
        pascalCaseTag: true,
        template: (svg) => native(svg, name, allowOverrideFill),
      });

    const trsfNativeForTs = () =>
      trsf({
        js: true,
        pascalCaseTag: true,
        template: (svg) => nativeForTypescript(svg, name, allowOverrideFill),
      });

    const trsfWeb = () =>
      trsf({
        js: true,
        pascalCaseTag: false,
        template: (svg) => web(svg, name, allowOverrideFill),
      });

    const trsfWebForTs = () =>
      trsf({
        js: true,
        pascalCaseTag: false,
        template: (svg) => webForTypescript(svg, name, allowOverrideFill),
      });

    if (
      !withNative &&
      !withNativeForTypescript &&
      !withWeb &&
      !withWebForTypescript
    ) {
      return acc;
    }

    const newFiles: File[] = [];

    if (withNative) {
      newFiles.push({
        name: file.name + ".js",
        content: trsfNative(),
      });
    }

    if (withNativeForTypescript) {
      newFiles.push({
        name: file.name + ".tsx",
        content: trsfNativeForTs(),
      });
    }

    const webExtension = withNative || withNativeForTypescript ? ".web" : "";

    if (withWeb) {
      newFiles.push({
        name: file.name + webExtension + ".js",
        content: trsfWeb(),
      });
    }

    if (withWebForTypescript) {
      newFiles.push({
        name: file.name + webExtension + ".tsx",
        content: trsfWebForTs(),
      });
    }

    return [...acc, ...newFiles];
  }, [] as File[]);
};

const write = (outputPath: string, files: File[]): File[] => {
  files.forEach((file) => {
    const filename = join(outputPath, makeName(file.name));
    mkdirp.sync(dirname(filename));
    writeFileSync(filename, file.content, "utf8");
  });
  return files;
};

export const make = async (
  [sourcePath, outputPath]: [string, string],
  flags: Flags,
): Promise<File[]> => {
  const files = await get(join(sourcePath, "*.svg"));
  console.log("Files found", files.length);

  const transformedFiles = transformFiles(shortenFilenames(sourcePath, files), {
    withNative: flags.withNative ?? false,
    withNativeForTypescript: flags.withNativeForTypescript ?? false,
    withWeb: flags.withWeb ?? false,
    withWebForTypescript: flags.withWebForTypescript ?? false,
    removeFill: flags.removeFill ?? false,
    removeStroke: flags.removeStroke ?? false,
    allowOverrideFill: flags.allowOverrideFill ?? false,
  });

  console.log("Files transformed", transformedFiles.length);

  const writtenFiles = write(outputPath, transformedFiles);
  console.log("Files written", writtenFiles.length);

  return writtenFiles;
};
