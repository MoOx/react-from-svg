#!/usr/bin/env node
"use strict";
const meow = require("meow");

// UPDATE README IF YOU UPDATE THIS PLEASE
const cli = meow(
  `
  Usage
    $ react-from-svg <sourcePath> <outputPath> [--with-native|--with-web]

  Options
    --with-native, -native  Output code for react-native-svg
    --with-web, -web        Output code for DOM. If --with-native is also used, will be output as .web.js files
    --with-reason, -bs      Output ReasonML bindings code
    --remove-fill, -rf      Remove all 'fill' properties from SVGs, convenient for icons
    --remove-stroke, -rs    Remove all 'stroke' properties from SVGs, convenient for icons
    --commonjs, -cjs        Export as commonjs instead of es6 import/export
    --bs-module-path, -bsp  Allow to customise ReasonML output path

  Example
    $ react-from-svg assets/svgs src/Svgs --remove-fill
`,
  {
    flags: {
      "with-native": { type: "boolean", alias: "native" },
      "with-web": { type: "boolean", alias: "web" },
      "with-reason": { type: "boolean", alias: "bs" },
      "remove-fill": { type: "boolean", alias: "rf" },
      "remove-stroke": { type: "boolean", alias: "rs" },
      commonjs: { type: "boolean", alias: "cjs" },
      "bs-module-path": { type: "string", alias: "bsp" },
    },
  },
);

if (cli.flags.withNative === undefined && cli.flags.withWeb === undefined) {
  console.error(
    "You should at least choose an option between --with-native or --with web!",
  );
  cli.showHelp();
  process.exit(1);
}

///

let compiledArtifact = "./lib/js/src/Transformer.bs.js";
let transformer;
try {
  transformer = require(compiledArtifact);
} catch (e) {
  console.log(
    "react-from-svg: Missing compiled " + compiledArtifact + ", rebuilding",
  );
  require("child_process").execSync("bsb -clean-world -make-world", {
    cwd: __dirname,
    stdio: "inherit",
  });
}

setTimeout(function() {
  try {
    delete require.cache[compiledArtifact];
    transformer = require(compiledArtifact);
  } catch (e) {
    throw new Error(
      "react-from-svg: missing compiled script. You might have used a `bsb -clean-world` which is currently causing trouble to the way this bin is generated." +
        "\n" +
        "***************************************************************************************************************" +
        "\n" +
        "** Try running this command again, we tried to compile it asynchronously (should be ready as you read this). **" +
        "\n" +
        "***************************************************************************************************************" +
        "\n" +
        "If this issue persist, open an issue with as much as information as you can (bsconfig, etc) https://github.com/MoOx/react-from-svg/issues/new",
    );
  }

  transformer.make(cli.input, cli.flags);
}, 0);
