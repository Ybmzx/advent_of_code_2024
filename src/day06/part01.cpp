#include <iostream>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
const int N = 1e3 + 10;
char mp[N][N];
bool visited[N][N];
int n = 0;

struct Point {
    int x, y;
};

const Point dir[] = {
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 },
};

Point get_guard_position() {
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= n; j ++)
            if (mp[i][j] == '^')
                return { i, j };
    return { -1, -1 };
}

bool in_bounds(Point x) {
    return x.x >= 1 && x.x <= n &&
        x.y >= 1 && x.y <= n;
}

int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    while (fgets(mp[++ n] + 1, sizeof(char) * N, stdin));
    n --;

    Point pos = get_guard_position();

    int k = 0, ans = 1;
    visited[pos.x][pos.y] = true;
    while (in_bounds(pos)) {
        Point nxt = { pos.x + dir[k].x, pos.y + dir[k].y };
        if (in_bounds(nxt) && mp[nxt.x][nxt.y] == '#') {
            k = (k + 1) % 4;
            continue;
        }
        pos = nxt;
        if (in_bounds(pos) && !visited[pos.x][pos.y]) {
            ans ++;
        }
        visited[pos.x][pos.y] = true;
    }

    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}