const fs = require('fs');
const readline = require('readline');

const rl = readline.createInterface({
  input: fs.createReadStream(process.argv[2]),
});

digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']

function digit_value(index) {
  if (index <= 9)
    return String(index)
  else
    return String(index-9)
}

function fst_digit(line) {
  let min = line.length-1, line_index, digit_index;
  for (let i = 0; i < digits.length; i++) {
    d = digits[i];
    line_index = line.indexOf(d);
    if (line_index != -1 && line_index <= min) {
      min = line_index
      digit_index = i
    }
  }
  return digit_value(digit_index)
}

function snd_digit(line) {
  let max = 0, line_index, digit_index;
  for (let i = 0; i < digits.length; i++) {
    d = digits[i];
    line_index = line.lastIndexOf(d);
    if (line_index != -1 && line_index >= max) {
      max = line_index
      digit_index = i
    }
  }
  return digit_value(digit_index)
}

function get_calib(line) {
  let fst = fst_digit(line);
  let snd = snd_digit(line);
  return +(fst+snd);   // sum as strings, but return int value
}

let sum = 0;

rl.on('line', (line) => {
  sum += get_calib(line);
});

rl.on('close', () => {
  console.log(sum);
});
