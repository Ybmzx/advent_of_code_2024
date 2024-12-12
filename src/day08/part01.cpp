#include <iostream>
#include <map>
#include <vector>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
const int N = 1e3 + 10;
char mp[N][N];
bool antinodes[N][N];
int n = 0, ans = 0;
struct Point {
    int x, y;
};
map<char, vector<Point>> antennases;

Point get_antinode(Point a, Point b) {
    return { a.x + -(b.x - a.x), a.y + -(b.y - a.y) };
}

int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    while (fgets(mp[++ n] + 1, sizeof(char) * N, stdin));
    n --;

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (mp[i][j] != '.') antennases[mp[i][j]].push_back({ i, j });
        }
    }

    for (auto&& p : antennases) {
        auto&& vec = p.second;
        for (int i = 0; i < vec.size(); i ++) {
            for (int j = 0; j < vec.size(); j ++) {
                if (i == j) continue;
                Point antinode_pos = get_antinode(vec[i], vec[j]);
                if (!(antinode_pos.x <= n && antinode_pos.y <= n &&
                    antinode_pos.x > 0 && antinode_pos.y > 0  )) continue;
                ans += !antinodes[antinode_pos.x][antinode_pos.y];
                antinodes[antinode_pos.x][antinode_pos.y] = true;
            }
        }
    }
    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}