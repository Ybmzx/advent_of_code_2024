#include <iostream>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
const int N = 1e3 + 10;
char mp[N][N];
bool check(int x, int y) {
    if (mp[x][y] != 'A') return false;
    return ((mp[x - 1][y - 1] == 'M' && mp[x + 1][y + 1] == 'S') ||
            (mp[x - 1][y - 1] == 'S' && mp[x + 1][y + 1] == 'M')) &&
           ((mp[x + 1][y - 1] == 'M' && mp[x - 1][y + 1] == 'S') ||
            (mp[x + 1][y - 1] == 'S' && mp[x - 1][y + 1] == 'M'));
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