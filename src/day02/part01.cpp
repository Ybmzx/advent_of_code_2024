#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
vector<int> vec;

bool check(bool increase, int k = 0) {
    if (k >= vec.size()) return true;
    if (k == 0) return check(increase, k + 1);
    int curr = vec[k], last = vec[k - 1];
    if ((increase && curr <= last) ||
        !increase && curr >= last ||
        (abs(curr - last) > 3 || abs(curr - last) < 1))
            return false;
    return check(increase, k + 1);
}

int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    int ans = 0;
    string line;
    while (getline(cin, line)) {
        vec.clear();
        int t = 0;
        for (char it : line) {
            if (!isdigit(it)) {
                vec.push_back(t), t = 0;
                continue;
            }
            t = t * 10 + it - '0';
        }
        vec.push_back(t);
        bool increase = vec[0] < vec[1];
        if (check(increase)) ans ++;
    }

    cout << ans << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}