const path = require("path");

module.exports = {
  mode: "production",
  entry: "./src/bin.js",
  output: {
    filename: "bin.js",
    libraryTarget: "commonjs",
  },
  target: "node",
  externals: {
    meow: "meow",
    camelcase: "camelcase",
    glob: "glob",
    mkdirp: "mkdirp",
  },
};
