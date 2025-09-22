#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

int n;
vector<pii> points;
vector<int> radius;
vector<vector<int>> g;
vector<int> color;
bool valid;

void dfs(int u, int c, int &cnt0, int &cnt1) {
    color[u] = c;
    if (c == 0)
        cnt0++;
    else
        cnt1++;

    for (int v: g[u]) {
        if (color[v] == -1) {
            dfs(v, c ^ 1, cnt0, cnt1);
        } else if (color[v] == c) {
            valid = false;
        }
    }
}

void solve() {
    cin >> n;
    points.resize(n + 1);
    radius.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int x, y, r;
        cin >> x >> y >> r;
        points[i] = {x, y};
        radius[i] = r;
    }

    g.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            auto [x1, y1] = points[i];
            auto [x2, y2] = points[j];
            int dx = x1 - x2, dy = y1 - y2;
            int d_sq = dx * dx + dy * dy;
            int r_sum = radius[i] + radius[j];
            if (d_sq == r_sum * r_sum) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    color.assign(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            int cnt0 = 0, cnt1 = 0;
            valid = true;
            dfs(i, 0, cnt0, cnt1);
            if (valid && cnt0 != cnt1) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
