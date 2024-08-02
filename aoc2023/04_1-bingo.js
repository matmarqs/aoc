const fs = require('fs');
const readline = require('readline');

const rl = readline.createInterface({
  input: fs.createReadStream(process.argv[2]),
});

function analyzeCard(line) {
  winning = line.split(": ")[1].split("|")[0].trim().split(" ").filter(e => e !== '');
  ourNums = line.split(": ")[1].split("|")[1].trim().split(" ").filter(e => e !== '');
  let count = 0;
  for (let n = 0; n < ourNums.length; n++)
    if (winning.includes(ourNums[n]))
      count += 1;
  return (count === 0) ? 0 : 2**(count - 1)
}

let sum = 0;

rl.on('line', (line) => {
  sum += analyzeCard(line);
});

rl.on('close', () => {
  console.log(sum);
});
