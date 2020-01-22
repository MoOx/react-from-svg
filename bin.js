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

///

let compiledArtifact = "./lib/js/src/Transformer.bs.js";
let transformer;
try {
  transformer = require(compiledArtifact)
}
catch(e) {
  console.log("react-from-svg: Missing compiled "+compiledArtifact+", rebuilding");
  require("child_process")
  .execSync("bsb -clean-world -make-world", {
    cwd: __dirname,
    stdio: "inherit",
  });
}

setTimeout(function () {
  try {
    delete require.cache[compiledArtifact];
    transformer = require(compiledArtifact)
  }
  catch(e) {
    throw new Error(
      "react-from-svg: missing compiled script. You might have used a `bsb -clean-world` which is currently causing trouble to the way this bin is generated."
      +"\n"+
      "***************************************************************************************************************"
      +"\n"+
      "** Try running this command again, we tried to compile it asynchronously (should be ready as you read this). **"
      +"\n"+
      "***************************************************************************************************************"
      +"\n"+
      "If this issue persist, open an issue with as much as information as you can (bsconfig, etc) https://github.com/MoOx/react-from-svg/issues/new"
    )
  };

  transformer.make(sourcePath, outputPath, args.includes("--with-reason"), args.includes("--remove-fill"));
}, 0);
