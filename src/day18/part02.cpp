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
    bool operator!=(const Point& obj) const {
        return !(obj == *this);
    }
};
Point points[M];
Point dir[] = {
    {  0, -1 },
    {  0, 1 },
    {  1, 0 },
    {  -1, 0 },
};
bool vis[N + 5][N + 5];
Point dsu[N + 5][N + 5];

Point find(Point x) {
    if (dsu[x.x][x.y] != x) return dsu[x.x][x.y] = find(dsu[x.x][x.y]);
    return x;
}

int init_dsu() {
    for (int i = 0; i <= n; i ++)
        for (int j = 0; j <= n; j ++)
            dsu[i][j] = { i, j };

    for (int i = 0; i <= n; i ++) {
        for (int j = 0; j <= n; j ++) {
            if (vis[i][j]) continue;
            if (grids[i][j] == '#') continue;
            queue<Point> Q;
            Q.push({ i, j });
            while (!Q.empty()) {
                Point curr = Q.front(); Q.pop();
                for (int i = 0; i < 4; i ++) {
                    Point next = dir[i] + curr;
                    if (grids[next.x][next.y] != '#' &&
                        next.x >= 0 && next.x <= n &&
                        next.y >= 0 && next.y <= n &&
                        !vis[next.x][next.y]) {
                        Q.push(next);
                        vis[next.x][next.y] = true;
                        dsu[next.x][next.y] = find(curr);
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    while (scanf("%d,%d", &points[m].x, &points[m].y) != EOF) m ++;

    memset(grids, '.', sizeof grids);
    for (int i = 0; i < m; i ++) {
        swap(points[i].x, points[i].y);
        grids[points[i].x][points[i].y] = '#';
    }

    init_dsu();
    Point begin = { 0, 0 }, end = { n, n };
    for (int i = m - 1; i >= 0; i --) {
        grids[points[i].x][points[i].y] = '.';
        for (int j = 0; j < 4; j ++) {
            Point poi = dir[j] + points[i];
            if (poi.x < 0 || poi.x > n || poi.y < 0 || poi.y > n || grids[poi.x][poi.y] == '#') continue;
            Point parent = find(poi);
            dsu[parent.x][parent.y] = find(points[i]);
            if (find(begin) == find(end)) {
                cout << points[i].y << ',' << points[i].x;
                return 0;
            }
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}