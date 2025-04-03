#!/usr/bin/env node

import { execSync } from "node:child_process";
import { mkdirSync, existsSync, rmSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const optionalFlags = [
  { name: "remove-fill", alias: "rf", bool: true },
  { name: "remove-stroke", alias: "rs", bool: true },
];

// Create specific core combinations as requested
const coreCombinations = [
  // Group 1: with-native alone
  [{ name: "with-native", alias: "rn", bool: true }],

  // Group 2: with-native + with-web
  [
    { name: "with-native", alias: "rn", bool: true },
    { name: "with-web", alias: "rnw", bool: true },
  ],

  // Group 3: with-native-for-typescript alone
  [{ name: "with-native-for-typescript", alias: "rnts", bool: true }],

  // Group 4: with-native-for-typescript + with-web-for-typescript
  [
    { name: "with-native-for-typescript", alias: "rnts", bool: true },
    { name: "with-web-for-typescript", alias: "rnwts", bool: true },
  ],
];

// Helper function to generate combinations of other options with with-native-for-typescript
function generateOtherOptionCombinations() {
  const baseTsOption = {
    name: "with-native-for-typescript",
    alias: "rnts",
    bool: true,
  };
  const result = [];

  // Generate combinations of other options
  optionalFlags.forEach((option) => {
    result.push([baseTsOption, option]);
  });

  // Also test all other options together
  if (optionalFlags.length > 0) {
    result.push([baseTsOption, ...optionalFlags]);
  }

  return result;
}

const allCombinations = [
  ...coreCombinations,
  ...generateOtherOptionCombinations(),
];

// Create output directory if it doesn't exist
const outputBaseDir = path.join(__dirname, "../tests/components");
if (existsSync(outputBaseDir)) {
  rmSync(outputBaseDir, { recursive: true, force: true });
}
mkdirSync(outputBaseDir, { recursive: true });

console.log(`Testing ${allCombinations.length} combinations...`);

// Run each combination
for (let i = 0; i < allCombinations.length; i++) {
  const combination = allCombinations[i];

  // Create option string for command
  const optionsString = combination.map((opt) => `--${opt.name}`).join(" ");

  // Create directory name from combination
  const dirName = combination
    .map((opt) => opt.name)
    .join("_")
    .replace(/\-/g, "-");

  const outputDir = path.join(outputBaseDir, dirName);
  mkdirSync(outputDir, { recursive: true });

  // Build and execute the command
  const command = `node ./dist/bin.js tests/fixtures ${outputDir} ${optionsString}`;

  try {
    console.log(`[${i + 1}/${allCombinations.length}] Running: ${command}`);
    execSync(command, { stdio: "inherit" });

    // Run prettier on generated files to fix formatting issues (including escaped quotes)
    console.log(`Running prettier on ${outputDir}`);
    try {
      execSync(`npx prettier --write "${outputDir}/**/*.{js,jsx,ts,tsx}"`, {
        stdio: "inherit",
      });
    } catch (prettierError: unknown) {
      console.error(`⚠️ Prettier failed for ${dirName}:`);
      console.error(prettierError);
      // Exit immediately if prettier fails
      process.exit(1);
    }

    console.log(`✅ Completed: ${dirName}`);
  } catch (error: unknown) {
    console.error(`❌ Failed: ${dirName}`);
    console.error(error);
    // Exit immediately if any combination fails
    process.exit(1);
  }
}

console.log("All combinations tested!");
