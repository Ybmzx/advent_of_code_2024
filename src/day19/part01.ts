const input = await Deno.readTextFile("./input.in");
const patterns = new Set(input.split(/\r?\n\r?\n/)[0].split(', '));
const designs = input.split(/\r?\n\r?\n/)[1].split(/\r?\n/);

function isDesignPossible(design: string, patterns: Set<string>): boolean {
    const dp = new Array<boolean>(design.length + 5).fill(false);
    dp[0] = true;
    for (let i = 0; i < design.length; i ++) {
        for (let j = 0; j <= i; j ++) {
            if (dp[j] && patterns.has(design.slice(j, i + 1))) {
                dp[i + 1] = true;
                break;
            }
        }
    }
    return dp[design.length];
}

let answer = 0;
for (const design of designs) {
    answer += isDesignPossible(design, patterns) ? 1 : 0;
}
console.log(answer);
