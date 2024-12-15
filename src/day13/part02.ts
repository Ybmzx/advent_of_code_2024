const input = await Deno.readTextFile("./input.in");

const blocks = input.split(/\r?\n\r?\n/);
const OFFSET = 10000000000000;

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
        prize: [OFFSET + prize[0], OFFSET + prize[1]]
    });
}

function isInt(x: number) {
    return x % 1 === 0;
}

function solveGame(game: Game): [number, number] {
    const D = game.buttonA[0] * game.buttonB[1] -
        game.buttonA[1] * game.buttonB[0];
    if (D === 0) return [-1, -1];
    const Dx = game.prize[0] * game.buttonB[1] - game.prize[1] * game.buttonB[0];
    const Dy = game.prize[1] * game.buttonA[0] - game.prize[0] * game.buttonA[1];
    const result: [number, number] = [Dx / D, Dy / D];

    if (!isInt(result[0]) || !isInt(result[1]))
        return [-1, -1];

    return result;
}

let answer = 0;

for (const game of games) {
    const result = solveGame(game);
    if (result[0] === -1 && result[1] === -1) continue;
    answer += result[0] * 3 + result[1];
}

console.log(answer);