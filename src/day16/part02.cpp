#include <cstring>
#include <queue>
#include <iostream>
#include <vector>
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
    bool operator!=(const Point& obj) {
        return obj.x != this->x || obj.y != this->y;
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
vector<State> prev_points[N][N][4];

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
            if (new_score <= score[next.x][next.y][next_direction] &&
                grids[next.x][next.y] != '#') {
                if (new_score == score[next.x][next.y][next_direction]) {
                    prev_points[next.x][next.y][next_direction].push_back({ curr.position, d });
                    continue;
                }

                Q.push({ next, next_direction, new_score });
                score[next.x][next.y][next_direction] = new_score;
                prev_points[next.x][next.y][next_direction].clear();
                prev_points[next.x][next.y][next_direction].push_back({ curr.position, d });
            }
        }
    }
}

int mark_path(Point last, int direction) {
    int cnt = grids[last.x][last.y] != 'O';
    grids[last.x][last.y] = 'O';
    for (State s : prev_points[last.x][last.y][direction]) {
        cnt += mark_path(s.position, s.direction);
    }
    return cnt;
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
    int min_idx = -1;
    for (int i = 0; i < 4; i ++) {
        if (min_idx == -1 || score[end.x][end.y][i] < score[end.x][end.y][min_idx]) {
            min_idx = i;
        }
    }

    cout << mark_path(end, min_idx);

    fclose(stdin);
    fclose(stdout);
    return 0;
}