// utils.js
const fs = require("fs");
const path = require("path");

function parseArguments() {
  const args = process.argv.slice(2); // Skip node and script path
  let inputFile = null;
  let isPartTwo = false;

  // Parsing arguments
  args.forEach(arg => {
    if (arg === "--two") {
      isPartTwo = true; // Set flag if --two is found
    } else if (!inputFile) {
      inputFile = arg; // Treat the first non-flag argument as the input file
    } else {
      console.error(`Unexpected argument: ${arg}`);
      process.exit(1);
    }
  });

  // Check if the input file was provided
  if (!inputFile) {
    console.error(`Usage: ./${path.basename(process.argv[1])} <inputfile> [--two]`);
    process.exit(1);
  }

  // Read and return the input file content
  const input = fs.readFileSync(inputFile, "utf8").trim();
  return { input, isPartTwo };
}

module.exports = { parseArguments };
