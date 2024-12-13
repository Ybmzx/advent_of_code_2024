#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e2 + 10;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
int dir[][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};
char mp[N][N];
int n = 0;
bool vis[N][N];
int dfs(int x, int y) {
    if (mp[x][y] == '9') {
        return !vis[x][y] && (vis[x][y] = true);
    }
    int res = 0;
    for (int i = 0; i < 4; i ++) {
        int nx = x + dir[i][0], ny = y + dir[i][1];
        if (nx > 0 && nx <= n &&
            ny > 0 && ny <= n &&
            mp[nx][ny] - mp[x][y] == 1)
                res += dfs(nx, ny);
    }
    return res;
}
int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    while (fgets(mp[++ n] + 1, sizeof(char) * N, stdin));
    n --;
    int ans = 0;
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= n; j ++)
            if (mp[i][j] == '0') {
                memset(vis, 0, sizeof vis);
                ans += dfs(i, j);
            }

    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}