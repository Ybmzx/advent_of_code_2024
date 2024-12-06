#include <iostream>
#include <vector>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
const int N = 1e3 + 10;
char mp[N][N];
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

bool has_loop(Point pos) {
    int k = 0, ans = 1;
    // bool visited[N][N][4], 状态压缩
    vector<vector<int>> visited(n + 5, vector<int>(n + 5, 0));
    visited[pos.x][pos.y] |= 1 << k;
    while (in_bounds(pos)) {
        Point nxt = { pos.x + dir[k].x, pos.y + dir[k].y };
        if (in_bounds(nxt) && mp[nxt.x][nxt.y] == '#') {
            k = (k + 1) % 4;
            continue;
        }
        pos = nxt;
        if (visited[pos.x][pos.y] >> k & 1) return true;
        visited[pos.x][pos.y] |= 1 << k;
    }
    return false;
}

int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    while (fgets(mp[++ n] + 1, sizeof(char) * N, stdin));
    n --;

    Point pos = get_guard_position();

    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (mp[i][j] != '.') continue;
            mp[i][j] = '#';
            ans += has_loop(pos);
            mp[i][j] = '.';
        }
    }

    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}