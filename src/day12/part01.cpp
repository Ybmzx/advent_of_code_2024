#include <iostream>
#include <queue>
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

pair<int, int> get_area_and_number_of_sides(Point position) {
    const char current = mp[position.x][position.y];
    int area = 0, perimeter = 0;
    queue<Point> Q;
    Q.push({ position.x, position.y });
    while (!Q.empty()) {
        Point k = Q.front(); Q.pop();
        if (visited[k.x][k.y]) continue;
        visited[k.x][k.y] = true;
        area ++;
        for (int i = 0; i < 4; i ++) {
            Point nxt = { k.x + dir[i].x, k.y + dir[i].y };
            if (!in_bounds(nxt) || mp[nxt.x][nxt.y] != current) {
                perimeter ++;
                continue;
            }
            if (visited[nxt.x][nxt.y]) continue;
            Q.push(nxt);
        }
    }
    return { area, perimeter };
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