#include <iostream>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
const int N = 1e3 + 10;
char mp[N][N];
const auto XMAS = "XMAS";
const int dir[][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
    {1, 1},
    {1, -1},
    {-1, -1},
    {-1, 1}
};

bool check_dir(int x, int y, const int dir[]) {
    for (int i = 0; i < 4; i ++) {
        if (mp[x + i * dir[0]][y + i * dir[1]] != XMAS[i])
            return false;
    }
    return true;
}

int check(int x, int y) {
    int ans = 0;
    for (int i = 0; i < 8; i ++) {
        ans += check_dir(x, y, dir[i]);
    }
    return ans;
}

int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    int n = 0;
    while (fgets(mp[++ n] + 1, N * sizeof(char), stdin));
    n --;

    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            ans += check(i, j);
        }
    }
    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}