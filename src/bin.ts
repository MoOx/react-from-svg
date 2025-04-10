#!/usr/bin/env node

import meow from "meow";
import { make } from "./transformer.js";

const cli = meow(
  `
  Usage
    $ react-from-svg <sourcePath> <outputPath> [--with-native|--with-web]

  Options
    --with-native, -rn                    Output code for react-native-svg
    --with-native-for-typescript, -rnts   Output code for react-native-svg with TypeScript
    --with-web, -rnw                      Output code for DOM. If --with-native is also used, will be output as .web.js files
    --with-web-for-typescript, -rnwts     Output code for DOM with TypeScript. If --with-native is also used, will be output as .web.tsx files
    --remove-fill, -rf                    Remove all 'fill' properties from SVGs, convenient for icons
    --remove-stroke, -rs                  Remove all 'stroke' properties from SVGs, convenient for icons

  Example
    $ react-from-svg assets/svgs src/Svgs --with-native --remove-fill
`,
  {
    importMeta: import.meta,
    flags: {
      withNative: { type: "boolean", shortFlag: "rn" },
      withNativeForTypescript: { type: "boolean", shortFlag: "rnts" },
      withWeb: { type: "boolean", shortFlag: "rnw" },
      withWebForTypescript: { type: "boolean", shortFlag: "rnwts" },
      removeFill: { type: "boolean", shortFlag: "rf" },
      removeStroke: { type: "boolean", shortFlag: "rs" },
    },
  },
);

if (
  cli.flags.withNative === undefined &&
  cli.flags.withNativeForTypescript === undefined &&
  cli.flags.withWeb === undefined &&
  cli.flags.withWebForTypescript === undefined
) {
  console.error(
    "You should at least choose an output option (one of --with-*)!",
  );
  cli.showHelp();
  process.exit(1);
}

make(cli.input as [string, string], cli.flags);
