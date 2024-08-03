const fs = require('fs');

class Map {
  constructor(name, rules) {
    this.name = name;
    this.rules = rules;
  }
}

let maps = []
// get all the maps
fs.readFile(process.argv[2], 'utf8', (err, data) => {
  if (err) { console.error(err); return; }
  let lines = data.split('\n');
  let seeds = lines[0].split(": ")[1].split(" ")
  for (let l = 2; l < lines.length; l++) {
    let map_name = lines[l].split(" ")[0];
    let rules = [];
    while ((line = lines[++l]) !== '') {
      rules.push(line.split(" ").map(Number));
    }
    maps.push(new Map(map_name, rules));
  }

  let minx = Infinity;
  for (let s = 0; s < seeds.length; s++) {
    let x = seeds[s], fx = x;
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
  }
  console.log(minx);
});
