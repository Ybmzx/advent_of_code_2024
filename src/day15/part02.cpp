#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
const int N = 1e3 + 10;
int n = 0, m = 0;
char grids[N][N];
char wide_grids[N][N];
string operations;

struct Point {
    int x, y;
    Point operator+(const Point& obj) {
        return { obj.x + this->x, obj.y + this->y };
    }
};

void print_map() {
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            cout << wide_grids[i][j];
        }
        cout << '\n';
    }
}

Point get_robot_position() {
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++)
            if (wide_grids[i][j] == '@')
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

bool can_move_box(Point box_position, char direction) {
    if (wide_grids[box_position.x][box_position.y] != '[' &&
        wide_grids[box_position.x][box_position.y] != ']')
        return true;
    Point left = wide_grids[box_position.x][box_position.y] == '['
        ? box_position
        : box_position + Point { 0, -1 };
    Point right = left + Point { 0, 1 };
    Point next_left = left + get_direction(direction),
        next_right = right + get_direction(direction);
    if (direction == '>' || direction == '<') {
        Point next = direction == '>'
            ? right + Point { 0, 1 }
            : left + Point { 0, -1 };
        switch (wide_grids[next.x][next.y]) {
            case '#':
                return false;
            case '[':
            case ']': {
                return can_move_box(next, direction);
            }
            default:
                return true;
        }
        return true;
    }
    if (wide_grids[next_left.x][next_left.y] == '#' ||
        wide_grids[next_right.x][next_right.y] == '#')
            return false;
    if (wide_grids[next_left.x][next_left.y] == ']' ||
        wide_grids[next_left.x][next_left.y] == '[' ||
        wide_grids[next_right.x][next_right.y] == ']' ||
        wide_grids[next_right.x][next_right.y] == '[') {
        bool can_move = true;
        can_move &= can_move_box(next_left, direction);
        can_move &= can_move_box(next_right, direction);
        return can_move;
    }
    return true;
}

void move_box(Point box_position, char direction) {
    if (wide_grids[box_position.x][box_position.y] != '[' &&
        wide_grids[box_position.x][box_position.y] != ']')
        return;
    Point left = wide_grids[box_position.x][box_position.y] == '['
        ? box_position
        : box_position + Point { 0, -1 };
    Point right = left + Point { 0, 1 };
    Point next_left = left + get_direction(direction),
        next_right = right + get_direction(direction);
    if (direction == '>' || direction == '<') {
        Point next = direction == '>'
            ? right + Point { 0, 1 }
            : left + Point { 0, -1 };
        move_box(next, direction);
        wide_grids[left.x][left.y]
            = wide_grids[right.x][right.y]
            = '.';
        wide_grids[next_left.x][next_left.y] = '[';
        wide_grids[next_right.x][next_right.y] = ']';
        return;
    }
    move_box(next_left, direction);
    move_box(next_right, direction);
    wide_grids[left.x][left.y]
        = wide_grids[right.x][right.y]
        = '.';
    wide_grids[next_left.x][next_left.y] = '[';
    wide_grids[next_right.x][next_right.y] = ']';
}

bool try_move_box(Point box_position, char direction) {
    bool can_move = can_move_box(box_position, direction);
    if (can_move) move_box(box_position, direction);
    return can_move;
}

Point move_robot(Point robot_position, char direction) {
    Point next = robot_position + get_direction(direction);
    switch (wide_grids[next.x][next.y]) {
        case '#':
            return robot_position;
        case '[':
        case ']': {
            return try_move_box(next, direction) ? next : robot_position;
        }
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

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (grids[i][j] == '#')
                wide_grids[i][j * 2] = wide_grids[i][j * 2 - 1] = '#';
            else if (grids[i][j] == '.')
                wide_grids[i][j * 2] = wide_grids[i][j * 2 - 1] = '.';
            else if (grids[i][j] == '@') {
                wide_grids[i][j * 2] = '.';
                wide_grids[i][j * 2 - 1] = '@';
            }
            else {
                wide_grids[i][j * 2] = ']';
                wide_grids[i][j * 2 - 1] = '[';
            }
        }
    }
    m = n * 2;

    string operation;
    while (getline(cin, operation))
        operations += operation;

    Point robot = get_robot_position();
    for (char op : operations) {
        wide_grids[robot.x][robot.y] = '.';
        robot = move_robot(robot, op);
        wide_grids[robot.x][robot.y] = '@';
    }
    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            if (wide_grids[i][j] == '[')
                ans += (i - 1) * 100 + j - 1;
        }
    }
    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}