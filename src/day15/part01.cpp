#include <iostream>
#include <string>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
const int N = 1e3 + 10;
int n = 0;
char grids[N][N];
string operations;

struct Point {
    int x, y;
};

Point get_robot_position() {
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= n; j ++)
            if (grids[i][j] == '@')
                return { i, j };
    return { -1, -1 };
}

Point get_direction(char direction) {
    switch (direction) {
        case '^':
            return { -1, 0 };
        case 'v':
            return { 1, 0 };
        case '>':
            return { 0, 1 };
        case '<':
            return { 0, -1 };
    }
    return { 0,0 };
}

bool move_box(Point box_position, char direction) {
    Point next = {
        box_position.x + get_direction(direction).x,
        box_position.y + get_direction(direction).y
    };
    switch (grids[next.x][next.y]) {
        case '#': {
            return false;
        }
        case 'O': {
            bool result = move_box(next, direction);
            if (result) {
                grids[next.x][next.y] = 'O';
                grids[box_position.x][box_position.y] = '.';
            }
            return result;
        }
        default: {
            grids[next.x][next.y] = 'O';
            grids[box_position.x][box_position.y] = '.';
            return true;
        }
    }
}

Point move(Point robot_position, char direction) {
    Point next = {
        robot_position.x + get_direction(direction).x,
        robot_position.y + get_direction(direction).y
    };
    switch (grids[next.x][next.y]) {
        case '#':
            return robot_position;
        case 'O':
            return move_box(robot_position, direction) ? next : robot_position;
        default:
            return next;
    }
}

int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    while (fgets(grids[++ n] + 1, N * sizeof(char), stdin)
        && (grids[n][1] != '\n' && grids[n][1] != '\r'));
    n --;

    string operation;
    while (getline(cin, operation))
        operations += operation;

    Point robot = get_robot_position();
    for (char op : operations) {
        grids[robot.x][robot.y] = '.';
        robot = move(robot, op);
        grids[robot.x][robot.y] = '@';
    }
    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (grids[i][j] == 'O')
                ans += (i - 1) * 100 + j - 1;
        }
    }
    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}