#include <cstdio>
#include <iostream>
#include <unordered_map>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
const int N = 1e3 + 10;
int a[N], b[N], n = 1;
unordered_map<int, int> cnt;
int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    while (cin >> a[n] >> b[n]) {
        cnt[b[n]] ++;
        n ++;
    }
    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        ans += cnt[a[i]] * a[i];
    }
    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}