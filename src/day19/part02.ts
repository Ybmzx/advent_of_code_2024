const input = await Deno.readTextFile("./input.in");
const patterns = new Set(input.split(/\r?\n\r?\n/)[0].split(', '));
const designs = input.split(/\r?\n\r?\n/)[1].split(/\r?\n/);

function getPossibleWays(design: string, patterns: Set<string>): number {
    const dp = new Array<number>(design.length + 5).fill(0);
    dp[0] = 1;
    for (let i = 0; i < design.length; i ++) {
        for (let j = 0; j <= i; j ++) {
            if (dp[j] !== 0 && patterns.has(design.slice(j, i + 1))) {
                dp[i + 1] += dp[j];
            }
        }
    }
    return dp[design.length];
}

let answer = 0;
for (const design of designs) {
    answer += getPossibleWays(design, patterns);
}
console.log(answer);
