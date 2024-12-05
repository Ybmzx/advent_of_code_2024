const input = await Deno.readTextFile("./input.in");

const [inputRules, inputManuals] = input.split(/\s{4}/g);

const rules = new Map<number, Map<number, number>>();

for (const line of inputRules.split(/\r?\n/)) {
    const [before, after] = line.split('|').map(x => parseInt(x));
    if (!rules.has(before)) rules.set(before, new Map<number, number>());
    rules.get(before)!.set(after, -1);
    if (!rules.has(after)) rules.set(after, new Map<number, number>());
    rules.get(after)!.set(before, 1);
}

let ans = 0;

for (const line of inputManuals.split(/\r?\n/)) {
    const pages = line.split(',').map(x => parseInt(x));
    const sorted = pages.toSorted((a: number, b: number) => {
        return rules.get(a)?.get(b)
            ? rules.get(a)!.get(b)!
            : 0;
    });

    if (sorted.toString() === pages.toString()) {
        ans += sorted[Math.floor(sorted.length / 2)];
    }
}

console.log(ans);
