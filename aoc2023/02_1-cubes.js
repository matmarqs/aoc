const fs = require('fs');
const readline = require('readline');

const rl = readline.createInterface({
  input: fs.createReadStream(process.argv[2]),
});

types = ['red', 'green', 'blue']
maxcub = [ 12, 13, 14 ]

function isImpossible(cubes) {
  let red = 0, blue = 0, green = 0;
  for (c = 0; c < cubes.length; c++) {
    num = +cubes[c].split(" ")[0];
    typ = cubes[c].split(" ")[1];
    if (typ == 'red')
      red += num;
    else if (typ == 'green')
      green += num;
    else
      blue += num;
    if (red > maxcub[0] || green > maxcub[1] || blue > maxcub[2]) {
      //console.log(`Impossible: red = ${red}, green = ${green}, blue = ${blue}`);
      return 1;
    }
  }
  //console.log(`Possible: red = ${red}, green = ${green}, blue = ${blue}`)
  return 0;
}

function analyze_game(line) {
  game = line.split(": ")
  game_id = +game[0].split(" ")[1]   // get game_id as integer
  subsets = game[1].split(";");
  for (i = 0; i < subsets.length; i++) {
    cubes = subsets[i].trim();  // trim
    cubes = cubes.split(", ")
    if (isImpossible(cubes))
      return 0
  }
  return game_id
}

let sum = 0;
rl.on('line', (line) => {
  sum += analyze_game(line);
});

rl.on('close', () => {
  console.log(sum);
});
