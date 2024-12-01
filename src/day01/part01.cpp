#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
const int N = 1e3 + 10;
int a[N], b[N], n = 1;
int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    while (cin >> a[n] >> b[n]) n ++;
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);

    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        ans += abs(a[i] - b[i]);
    }
    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}