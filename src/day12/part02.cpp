#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
const int N = 1e3 + 10;
bool visited[N][N];
char mp[N][N];
int n = 0;
struct Point {
    int x, y;
};

const Point dir[] = {
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 },
};

bool in_bounds(Point x) {
    return x.x >= 1 && x.x <= n &&
        x.y >= 1 && x.y <= n;
}

struct Side {
    int x, y;
    bool inside_on_left_or_top;
};

pair<int, int> get_area_and_number_of_sides(Point position) {
    const char current = mp[position.x][position.y];
    int area = 0;
    auto horizontal_comparer = [](Side a, Side b) {
        if (a.inside_on_left_or_top != b.inside_on_left_or_top) return a.inside_on_left_or_top;
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    };
    auto vertical_comparer = [](Side a, Side b) {
        if (a.inside_on_left_or_top != b.inside_on_left_or_top) return a.inside_on_left_or_top;
        if (a.y == b.y) return a.x < b.x;
        return a.y < b.y;
    };
    vector<Side> horizontal;
    vector<Side> vertical;
    queue<Point> Q;
    Q.push({ position.x, position.y });
    while (!Q.empty()) {
        Point k = Q.front(); Q.pop();
        if (visited[k.x][k.y]) continue;
        visited[k.x][k.y] = true;
        area ++;
        for (int i = 0; i < 4; i ++) {
            Point nxt = { k.x + dir[i].x, k.y + dir[i].y };
            bool is_horizontal = dir[i].x != 0;
            bool inside_on_left_or_top = is_horizontal ? dir[i].x == -1 : dir[i].y == -1;
            if (!in_bounds(nxt) || mp[nxt.x][nxt.y] != current) {
                if (is_horizontal) horizontal.push_back({ nxt.x, nxt.y, inside_on_left_or_top });
                else vertical.push_back({ nxt.x, nxt.y, inside_on_left_or_top });
                continue;
            }
            if (visited[nxt.x][nxt.y]) continue;
            Q.push(nxt);
        }
    }
    int number_of_sides = 0;
    sort(horizontal.begin(), horizontal.end(), horizontal_comparer);
    for (int i = 0; i < horizontal.size(); i ++) {
        if (i == 0 ||
            horizontal[i].x != horizontal[i - 1].x ||
            horizontal[i].y - horizontal[i - 1].y != 1)
            number_of_sides ++;
    }
    sort(vertical.begin(), vertical.end(), vertical_comparer);
    for (int i = 0; i < vertical.size(); i ++) {
        if (i == 0 ||
            vertical[i].y != vertical[i - 1].y ||
            vertical[i].x - vertical[i - 1].x != 1)
            number_of_sides ++;
    }
    return { area, number_of_sides };
}

int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    while (fgets(mp[++ n] + 1, sizeof(char) * N, stdin));
    n --;

    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (visited[i][j]) continue;
            auto&& res = get_area_and_number_of_sides({ i, j });
            ans += res.first * res.second;
        }
    }
    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}