#include <iostream>
#include <vector>
using namespace std;
#define int long long
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
string disk;
struct Block {
    int val, cnt;
};
vector<Block> blocks;
int file_block_count = 0;
signed main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    cin >> disk;
    int ans = 0;
    for (int i = 0; i < disk.size(); i ++) {
        blocks.push_back(
            {
                i % 2 == 0 ? file_block_count ++ : -1,
                disk[i] - '0'
            }
        );
    }

    for (int i = blocks.size() - 1; i >= 0; i --) {
        if (blocks[i].val == -1) continue;
        for (int j = 0; j < i; j ++) {
            if (blocks[j].val != -1 || blocks[j].cnt < blocks[i].cnt) continue;
            int val = blocks[i].val, cnt = blocks[i].cnt;
            blocks[j].cnt -= blocks[i].cnt;
            blocks[i].val = -1;
            blocks.insert(
                blocks.begin() + j,
                Block { val, cnt }
            );
            i ++;
            break;
        }
    }
    int idx = 0;
    for (auto&& block : blocks) {
        if (block.val == -1) {
            idx += block.cnt;
            continue;
        }
        ans += ((idx + (idx + block.cnt - 1)) * block.cnt / 2) * block.val;
        idx += block.cnt;
    }
    cout << ans;
    fclose(stdin);
    fclose(stdout);
    return 0;
}