const fs = require('fs');
const readline = require('readline');

const rl = readline.createInterface({
  input: fs.createReadStream(process.argv[2]),
});

class Card {
  constructor(id, winning, numbers, matches) {
    this.numCopies = 1;
    this.id = id;
    this.winning = winning;
    this.numbers = numbers;
    this.matches = matches;
  }
}

function getCard(line) {
  let id = line.split(": ")[0].split(" ")[-1]
  let winning = line.split(": ")[1].split("|")[0].trim().split(" ").filter(e => e !== '');
  let numbers = line.split(": ")[1].split("|")[1].trim().split(" ").filter(e => e !== '');
  let matches = 0;
  for (let n = 0; n < numbers.length; n++)
    if (winning.includes(numbers[n]))
      matches += 1;
  cards.push(new Card(id, winning, numbers, matches));
}

let cards = [];
rl.on('line', (line) => {
  getCard(line);
});

rl.on('close', () => {
  let sum = 0;
  for (let i = 0; i < cards.length; i++) {
    for (let j = 0; j < cards[i].matches; j++) {
      cards[i+j+1].numCopies += cards[i].numCopies;
    }
    sum += cards[i].numCopies;
  }
  console.log(sum);
});
