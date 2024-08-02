const fs = require('fs');
const readline = require('readline');

const rl = readline.createInterface({
  input: fs.createReadStream(process.argv[2]),
});

types = ['red', 'green', 'blue']

function cubesEachColor(cubes) {
  let red = 0, green = 0, blue = 0;
  for (c = 0; c < cubes.length; c++) {
    num = +cubes[c].split(" ")[0];
    typ = cubes[c].split(" ")[1];
    if (typ == 'red')
      red += num;
    else if (typ == 'green')
      green += num;
    else
      blue += num;
  }
  return [red, green, blue];
}

function analyze_game(line) {
  let red, green, blue;
  let maxred = 0, maxgreen = 0, maxblue = 0;
  game = line.split(": ")
  game_id = +game[0].split(" ")[1]   // get game_id as integer
  subsets = game[1].split(";");
  for (i = 0; i < subsets.length; i++) {
    cubes = subsets[i].trim();  // trim
    cubes = cubes.split(", ")
    colors = cubesEachColor(cubes)
    red = colors[0]; green = colors[1]; blue = colors[2]
    maxred = (red > maxred) ? red : maxred
    maxgreen = (green > maxgreen) ? green : maxgreen
    maxblue = (blue > maxblue) ? blue : maxblue
  }
  return maxred * maxgreen * maxblue;
}

let sum = 0;
rl.on('line', (line) => {
  sum += analyze_game(line);
});

rl.on('close', () => {
  console.log(sum);
});
