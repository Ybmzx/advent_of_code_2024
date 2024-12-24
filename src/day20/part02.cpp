#include <iostream>
#include <map>
#include <ostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
using Point = pair<int, int>;
const int N = 1e3 + 10;
char grids[N][N];
int n = 0;
Point dir[] = {
    { 0, 1 },
    { 0, -1 },
    { 1, 0 },
    { -1, 0 },
};
Point operator+(const Point& a, const Point& b) {
    return { a.first + b.first, a.second + b.second };
}
struct State {
    Point pos;
    int step = 0;
};

bool in_bounds(Point poi) {
    return poi.first >= 1 && poi.first <= n &&
        poi.second >= 1 && poi.second <= n;
}

vector<vector<int>> bfs(Point start) {
    queue<State> Q;
    Q.push({ start, 0 });
    vector<vector<int>> dist(n + 5, vector<int>(n + 5, 0x3f3f3f3f));
    dist[start.first][start.second] = 0;
    while (!Q.empty()) {
        State curr = Q.front(); Q.pop();
        for (int i = 0; i < 4; i ++) {
            Point next = curr.pos + dir[i];
            if (in_bounds(next) &&
                grids[next.first][next.second] != '#' &&
                dist[next.first][next.second] >= 0x3f3f3f3f) {
                Q.push({ next, curr.step + 1 });
                dist[next.first][next.second] = curr.step + 1;
            }
        }
    }
    return dist;
}

Point find(char x) {
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (grids[i][j] == x)
                return { i, j  };
        }
    }
    return { -1, -1 };
}

int manhattan(Point a, Point b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void print_map() {
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cout << grids[i][j];
        }
        puts("");
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

    auto dist = bfs(start);

    const int max_picoseconds = 20;

    map<int, int> savings;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (grids[i][j] == '#') continue;
            for (int x = -max_picoseconds; x <= max_picoseconds; x ++) {
                int max_y = max_picoseconds - abs(x);
                for (int y = -max_y; y <= max_y; y ++) {
                    Point absolute_pos = { i + x, j + y };
                    if (!in_bounds(absolute_pos) ||
                        grids[absolute_pos.first][absolute_pos.second] == '#') continue;
                    int saved = dist[absolute_pos.first][absolute_pos.second] - dist[i][j] - manhattan(absolute_pos, { i, j });
                    if (saved > 0)
                        savings[saved] ++;
                }
            }
        }
    }

    int ans = 0;
    for (auto&& it : savings) {
        // cout << it.first << ' ' << it.second << '\n';
        ans += it.second * (it.first >= 100);
    }
    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}