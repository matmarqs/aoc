const fs = require('fs');
const readline = require('readline');

const rl = readline.createInterface({
  input: fs.createReadStream(process.argv[2]),
});

function isdigit(c) {
  return ('0' <= c) && (c <= '9');
}

function get_calib(line) {
  let fst, snd;
  for (let i=0; i < line.length; i++) {
    if (isdigit(line[i])) {
      fst = line[i];
      break;
    }
  }
  for (let i=line.length-1; i >= 0; i--) {
    if (isdigit(line[i])) {
      snd = line[i];
      break;
    }
  }
  return +(fst+snd);   // sum as strings, but return int value
}

let sum = 0;

rl.on('line', (line) => {
  sum += get_calib(line);
});

rl.on('close', () => {
  console.log(sum);
});
