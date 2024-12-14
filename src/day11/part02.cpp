#include <iostream>
#include <map>
#include <vector>
using namespace std;
#define int long long
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
int get_int_length(int x) {
    if (!x) return 1;
    int len = 0;
    while (x) {
        x /= 10;
        len ++;
    }
    return len;
}

pair<int, int> split_int(int x, int len) {
    pair<int, int> res;
    for (int i = 0, b = 1; i < len / 2; i ++){
        res.second += x % 10 * b;
        b *= 10;
        x /= 10;
    }
    for (int b = 1; x; ){
        res.first += x % 10 * b;
        b *= 10;
        x /= 10;
    }
    return res;
}

vector<int> update(int value) {
    if (value == 0) {
        return { 1 };
    }
    int len = get_int_length(value);
    if (len % 2 == 0) {
        auto&& splited = split_int(value, len);
        return { splited.first, splited.second };
    }
    return { value * 2024 };
}

map<int, int> blink(map<int, int> stones, int times) {
    for (int idx = 1; idx <= 75; idx ++) {
        map<int, int> new_stones;
        for (auto&& it : stones) {
            int value = it.first, count = it.second;
            auto&& updated = update(value);
            for (int i : updated) {
                new_stones[i] += count;
            }
        }
        stones = new_stones;
    }
    return stones;
}

signed main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    int v;
    map<int, int> stones;
    while (cin >> v) stones[v] = 1ll;

    stones = blink(stones, 75);

    int ans = 0;
    for (auto&& it : stones) ans += it.second;
    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}