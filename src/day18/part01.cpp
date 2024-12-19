#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
const int N = 70, M = 1e5 + 10;
char grids[N + 5][N + 5];
int n = N, m = 0;
struct Point {
    int x, y;
    Point operator+(const Point& obj) const {
        return { this->x + obj.x, this->y + obj.y };
    }
    bool operator==(const Point& obj) const {
        return this->x == obj.x && this->y == obj.y;
    }
};
Point points[M];
Point dir[] = {
    {  0, -1 },
    {  0, 1 },
    {  1, 0 },
    {  -1, 0 },
};

struct State {
    Point position;
    int step = 0;
};

bool vis[N + 5][N + 5];
int bfs(Point begin, Point end) {
    queue<State> Q;
    Q.push({ begin, 0 });
    while (!Q.empty()) {
        State curr = Q.front(); Q.pop();
        if (curr.position == end) {
            return curr.step;
        }
        for (int i = 0; i < 4; i ++) {
            Point next = dir[i] + curr.position;
            if (grids[next.x][next.y] != '#' &&
                next.x >= 0 && next.x <= n &&
                next.y >= 0 && next.y <= n &&
                !vis[next.x][next.y]) {

                Q.push({ next, curr.step + 1 });
                vis[next.x][next.y] = true;
            }
        }
    }
    return -1;
}

int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    while (scanf("%d,%d", &points[m].x, &points[m].y) != EOF) m ++;
    m --;

    memset(grids, '.', sizeof grids);
    for (int i = 0; i < 1024; i ++) {
        grids[points[i].y][points[i].x] = '#';
    }

    cout << bfs({ 0, 0 }, { n, n });

    fclose(stdin);
    fclose(stdout);
    return 0;
}