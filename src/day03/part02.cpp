#include <iostream>
#include <regex>
#include <string>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    long long ans = 0;

    string line;
    const regex reg(R"(mul\((\d+),(\d+)\)|(don't\(\))|(do\(\)))");
    bool calc = true;
    while (getline(cin, line)) {
        for (smatch match;
             regex_search(line, match, reg);
             line = match.suffix()) {
            if (match[4].matched) {
                calc = true;
                continue;
            }
            if (match[3].matched) {
                calc = false;
                continue;
            }
            if (!calc) continue;
            long long a = stoi(match[1]), b = stoi(match[2]);
            ans += a * b;
        }
    }

    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}