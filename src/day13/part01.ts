const input = await Deno.readTextFile("./input.in");

const blocks = input.split(/\r?\n\r?\n/);

type Game = {
    buttonA: [number, number],
    buttonB: [number, number],
    prize: [number, number]
};

const games = new Array<Game>();

for (const block of blocks) {
    const lines = block.split(/\r?\n/);
    const buttonA = lines[0].split(':')[1].split(',').map(x => parseInt(x.split('+')[1]));
    const buttonB = lines[1].split(':')[1].split(',').map(x => parseInt(x.split('+')[1]));
    const prize = lines[2].split(':')[1].split(',').map(x => parseInt(x.split('=')[1]));
    games.push({
        buttonA: [buttonA[0], buttonA[1]],
        buttonB: [buttonB[0], buttonB[1]],
        prize: [prize[0], prize[1]]
    });
}

function solveGame(game: Game): [number, number] {
    for (let i = 0; i <= 101; i ++) {
        for (let j = 0; j <= 101; j ++) {
            const to: [number, number] = [
                game.buttonA[0] * i + game.buttonB[0] * j,
                game.buttonA[1] * i + game.buttonB[1] * j
            ]
            if (to[0] === game.prize[0] && to[1] === game.prize[1]) {
                return [i, j];
            }
        }
    }
    return [-1, -1];
}

let answer = 0;

for (const game of games) {
    const result = solveGame(game);
    if (result[0] === -1 && result[1] === -1) continue;
    answer += result[0] * 3 + result[1];
}

console.log(answer);