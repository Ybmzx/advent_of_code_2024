const input = await Deno.readTextFile("./input.in");

const lines = input.split(/\r?\n/);
type Vector2D = [number, number];
type Robot = {
    position: Vector2D,
    velocity: Vector2D
};

const ROOM_SIZE: Vector2D = [101, 103];

const robots = new Array<Robot>();

for (const line of lines) {
    robots.push({
        position: line.split(' ')[0].split('=')[1].split(',').map(x => parseInt(x)) as Vector2D,
        velocity: line.split(' ')[1].split('=')[1].split(',').map(x => parseInt(x)) as Vector2D
    })
}

function move(robots: Array<Robot>, times: number = 1) {
    for (const robot of robots) {
        robot.position = [
            (robot.position[0] + robot.velocity[0] * times + ROOM_SIZE[0] * times) % ROOM_SIZE[0],
            (robot.position[1] + robot.velocity[1] * times + ROOM_SIZE[1] * times) % ROOM_SIZE[1]
        ]
    }
}

for (let i = 0; true; i++) {
    robots.sort((a, b) => {
        if (a.position[1] === b.position[1]) return a.position[0] - b.position[0]
        return a.position[1] - b.position[1];
    });
    let numberOfHorizontallyContiguousRobots = 0, maxn = 1;
    for (let i = 0; i < robots.length; i ++) {
        if (i === 0 || robots[i].position[0] - robots[i - 1].position[0] <= 1) {
            numberOfHorizontallyContiguousRobots ++;
            maxn = Math.max(maxn, numberOfHorizontallyContiguousRobots);
        }
        else {
            numberOfHorizontallyContiguousRobots = 1;
        }
    }
    if (maxn >= 31) {
        console.log(i);
        break;
    }
    move(robots);
}
