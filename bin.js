#!/usr/bin/env node

const args = process.argv.slice(0);
args.shift(); // node
args.shift(); // bin name
const sourcePath = args.shift();
const outputPath = args.shift();

const acceptedOptions = ["--with-reason", "--remove-fill"];

if (!sourcePath) {
  throw new Error("source path is required");
}
if (!outputPath) {
  throw new Error("output path is required");
}
if (args.filter(arg => !acceptedOptions.includes(arg)).length > 0) {
  throw new Error("only accepted options are: "+acceptedOptions);
}

let transformer;
try {
  transformer = require("./lib/js/src/Transformer.bs.js")
}
catch(e) {
  throw new Error("react-from-svg: impossible to get compiled Transformer module compiled from bs. Try reinstalling your dependencies or open an issue with as much as information as you can (bsconfig, etc) https://github.com/MoOx/react-from-svg/issues/new");
}

transformer.make(sourcePath, outputPath, args.includes("--with-reason"), args.includes("--remove-fill"));
