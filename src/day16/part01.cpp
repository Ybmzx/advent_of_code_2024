#include <cstring>
#include <queue>
#include <iostream>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
const int N = 1e3 + 10;
char grids[N][N];
int n = 0;

struct Point {
    int x, y;
    bool operator==(const Point& obj) {
        return obj.x == this->x && obj.y == this->y;
    }
    Point operator+(const Point& obj) {
        return { obj.x + this->x, obj.y + this->y };
    }
};

struct State {
    Point position;
    int direction;
    int score;
    bool operator>(const State& st) const {
        return this->score > st.score;
    }
};

Point find(char x) {
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (grids[i][j] == x)
                return { i, j };
        }
    }
    return { -1, -1 };
}

Point dir[] = {
    { 1, 0 }, // down
    { 0, 1 }, // right
    { -1, 0 }, // up
    { 0, -1 }, // left
};

// posX, posY, direction
bool visited[N][N][4];
int score[N][N][4];

void dijkstra(State start) {
    memset(score, 0x3f, sizeof score);
    priority_queue<State, vector<State>, greater<State>> Q;
    Q.push(start);
    score[start.position.x][start.position.y][start.direction] = start.score;
    while (!Q.empty()) {
        State curr = Q.top(); Q.pop();
        int x = curr.position.x,
            y = curr.position.y,
            d = curr.direction;
        if (visited[x][y][d])
            continue;
        visited[x][y][d] = true;

        for (int i : { -1, 0, 1 }) {
            int next_direction = (d + i + 4) % 4;
            int new_score = score[x][y][d] + 1 + 1000 * abs(i);
            Point next = curr.position + dir[next_direction];
            if (new_score < score[next.x][next.y][next_direction] &&
                grids[next.x][next.y] != '#') {
                Q.push({ next, next_direction, new_score });
                score[next.x][next.y][next_direction] = new_score;
            }
        }
    }
}

int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    while (fgets(grids[++ n] + 1, N * sizeof(char), stdin)
        && (grids[n][1] != '\n' && grids[n][1] != '\r'));
    n --;

    Point start = find('S'),
        end = find('E');
    dijkstra({ start, 1, 0 });
    cout << min(min(score[end.x][end.y][0], score[end.x][end.y][1]), min(score[end.x][end.y][2], score[end.x][end.y][3]));

    fclose(stdin);
    fclose(stdout);
    return 0;
}