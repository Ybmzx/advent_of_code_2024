#include <deque>
#include <iostream>
using namespace std;
#define int long long
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
string disk;
struct Block {
    int val, cnt;
};
deque<Block> blocks;
signed main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    cin >> disk;
    int ans = 0;
    for (int i = 0; i < disk.size(); i += 2) {
        blocks.push_back({ (int)blocks.size(), disk[i] - '0' });
    }
    int i = 0, idx = 0;
    while (!blocks.empty() && i < disk.size()) {
        if (i % 2 == 0) {
            int cnt = blocks.front().cnt;
            ans += ((idx + (idx + cnt - 1)) * cnt / 2) * blocks.front().val;
            idx += blocks.front().cnt;
            blocks.pop_front();
        }
        else {
            int cnt = min(blocks.back().cnt, (int)(disk[i] - '0'));
            disk[i] -= cnt;
            blocks.back().cnt -= cnt;
            ans += ((idx + (idx + cnt - 1)) * cnt / 2) * blocks.back().val;
            idx += cnt;
            if (blocks.back().cnt <= 0) {
                blocks.pop_back();
                continue;
            }
        }
        i ++;
    }
    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}