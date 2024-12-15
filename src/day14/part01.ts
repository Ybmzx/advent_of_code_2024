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

move(robots, 100);

const quadrant = [0, 0, 0, 0];
const axis: Vector2D = [Math.floor(ROOM_SIZE[0] / 2), Math.floor(ROOM_SIZE[1] / 2)];
for (const robot of robots) {
    const pos = robot.position;
    if (pos[0] > axis[0] && pos[1] < axis[1]) quadrant[0] ++;
    if (pos[0] < axis[0] && pos[1] < axis[1]) quadrant[1] ++;
    if (pos[0] < axis[0] && pos[1] > axis[1]) quadrant[2] ++;
    if (pos[0] > axis[0] && pos[1] > axis[1]) quadrant[3] ++;
}

console.log(quadrant[0] * quadrant[1] * quadrant[2] * quadrant[3]);
