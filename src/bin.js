const meow = require("meow");

// UPDATE README IF YOU UPDATE THIS PLEASE
const cli = meow(
  `
  Usage
    $ react-from-svg <sourcePath> <outputPath> [--with-native|--with-web]

  Options
    --with-native, -rn                    Output code for react-native-svg
    --with-web, -rnw                      Output code for DOM. If --with-native is also used, will be output as .web.js files
    --with-native-for-rescript, -rrn      Output code for @rescript-react-native/svg
    --with-web-for-rescript, -rrnw        Output code for @rescript/react
    --remove-fill, -rf                    Remove all 'fill' properties from SVGs, convenient for icons
    --remove-stroke, -rs                  Remove all 'stroke' properties from SVGs, convenient for icons
    --commonjs, -cjs                      Export as commonjs instead of es6 import/export

  Example
    $ react-from-svg assets/svgs src/Svgs --with-native --remove-fill
`,
  {
    flags: {
      "with-native": { type: "boolean", alias: "rn" },
      "with-web": { type: "boolean", alias: "rnw" },
      "with-native-for-rescript": { type: "boolean", alias: "rrn" },
      "with-web-for-rescript": { type: "boolean", alias: "rrnw" },
      "remove-fill": { type: "boolean", alias: "rf" },
      "remove-stroke": { type: "boolean", alias: "rs" },
      commonjs: { type: "boolean", alias: "cjs" },
    },
  },
);

if (
  cli.flags.withNative === undefined &&
  cli.flags.withWeb === undefined &&
  cli.flags.withNativeForReScript === undefined &&
  cli.flags.withWebForReScript === undefined
) {
  console.error(
    "You should at least choose an output option (one of --with-*)!",
  );
  cli.showHelp();
  process.exit(1);
}

require("./Transformer.bs.js").make(cli.input, cli.flags);
