const fs = require('fs');

class Map {
  constructor(name, rules) {
    this.name = name;
    this.rules = rules;
  }
}

let current = 0;

// return -1 if it is over
function nextSeed(seed, seeds) {
  if (current >= seeds.length)
    return -1;
  else if (seeds[current] <= seed && seed < seeds[current] + seeds[current+1]) {
    seed++;
    if (seed === seeds[current] + seeds[current+1] - 1)
      current += 2;
  }
  else
    seed = seeds[current];
  return seed;
}

fs.readFile(process.argv[2], 'utf8', (err, data) => {
  if (err) { console.error(err); return; }
  // get all the maps first
  let maps = [];
  let lines = data.split('\n');
  let seeds = lines[0].split(": ")[1].split(" ").map(Number)
  for (let l = 2; l < lines.length; l++) {
    let map_name = lines[l].split(" ")[0];
    let rules = [];
    while ((line = lines[++l]) !== '') {
      rules.push(line.split(" ").map(Number));
    }
    maps.push(new Map(map_name, rules));
  }

  let minx = Infinity;
  let current = 0, next;
  let seed = seeds[0];
  while (seed !== -1) {
    let x = seed;
    let fx = x;
    for (let m = 0; m < maps.length; m++) {
      rules = maps[m].rules
      for (let r = 0; r < rules.length; r++) {
        let dest = rules[r][0], src = rules[r][1], range = rules[r][2];
        if (src <= x && x < src + range)
          fx = dest + (x - src);
      }
      x = fx;
    }
    minx = (fx < minx) ? fx : minx;
    console.log(seed);
    seed = nextSeed(seed, seeds);
  }
  console.log(minx);
});
