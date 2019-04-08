#!/usr/bin/env node

const args = process.argv.slice(0);
args.shift(); // node
args.shift(); // bin name
const sourcePath = args.shift();
const outputPath = args.shift();

if (!sourcePath) {
  throw new Error("source path is required");
}
if (!outputPath) {
  throw new Error("output path is required");
}

require("./src/Transformer.bs.js").make(sourcePath, outputPath);
