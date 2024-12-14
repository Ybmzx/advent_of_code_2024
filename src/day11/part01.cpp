#include <iostream>
#include <list>
using namespace std;
#define int long long
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
int v;
list<int> lst;
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

signed main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    while (cin >> v) lst.push_back(v);

    for (int idx = 1; idx <= 25; idx ++) {
        for (auto it = lst.begin(); it != lst.end(); it ++) {
            if (*it == 0) {
                *it = 1;
                continue;
            }
            int len = get_int_length(*it);
            if (len % 2 == 0) {
                auto&& splited = split_int(*it, len);
                *it = splited.second;
                lst.insert(it, splited.first);
                continue;
            }
            *it *= 2024;
        }
    }

    cout << lst.size();

    fclose(stdin);
    fclose(stdout);
    return 0;
}