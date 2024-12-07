const input = await Deno.readTextFile("./input.in");

const lines = input.split(/\r?\n/);

function equations_can_be_true(
    testValue: number[],
    target: number,
    idx: number,
    sum: number
): boolean {
    if (sum > target) return false;
    if (idx >= testValue.length) {
        return sum == target;
    }
    return equations_can_be_true(testValue, target, idx + 1, sum + testValue[idx]) ||
        equations_can_be_true(testValue, target, idx + 1, sum * testValue[idx]) ||
        equations_can_be_true(testValue, target, idx + 1, parseInt(sum.toString() + testValue[idx].toString()));
}

let answer = 0;

for (const line of lines) {
    const target = parseInt(line.split(':')[0]);
    const testValue = line.split(':')[1]
        .split(' ')
        .filter(x => x.trim().length > 0)
        .map(x => parseInt(x));
    if (equations_can_be_true(testValue, target, 0, 0))
        answer += target;
}

console.log(answer);
