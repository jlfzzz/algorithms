#include <bits/stdc++.h>
#include <deque>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll

void init() {}

struct Point {
    int x, y, id;
};

void solve() {
    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].id = i + 1; // 1-indexed
    }

    // 1. 按x坐标排序
    sort(points.begin(), points.end(), [](const Point &a, const Point &b) { return a.x < b.x; });

    // 2. 前半部分按y坐标降序排列
    sort(points.begin(), points.begin() + n / 2, [](const Point &a, const Point &b) { return a.y > b.y; });

    // 3. 后半部分按y坐标升序排列
    sort(points.begin() + n / 2, points.end(), [](const Point &a, const Point &b) { return a.y < b.y; });

    // 4. 配对输出
    for (int i = 0; i < n / 2; i++) {
        cout << points[i].id << " " << points[i + n / 2].id << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
