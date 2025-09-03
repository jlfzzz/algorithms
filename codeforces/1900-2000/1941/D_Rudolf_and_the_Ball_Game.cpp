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

void solve() {
    int n, m, x;
    cin >> n >> m >> x;
    vector<pair<int, char>> info(m);
    For(i, m) {
        int t;
        cin >> t;
        char c;
        cin >> c;
        info[i] = {t, c};
    }

    set<pii> vis;
    set<int> ans;
    auto dfs = [&](this auto &&dfs, int i, int pos) -> void {
        if (vis.contains({i, pos})) {
            return;
        }

        if (i == m) {
            ans.insert(pos);
            return;
        }
        vis.insert({i, pos});
        int d = info[i].first;
        char c = info[i].second;

        if (c == '?') {
            dfs(i + 1, (pos + d) % n);
            dfs(i + 1, (pos - d + n) % n);
        } else if (c == '0') {
            dfs(i + 1, (pos + d) % n);
        } else { // c == '1'
            dfs(i + 1, (pos - d + n) % n);
        }
    };
    dfs(0, x - 1);

    cout << ans.size() << '\n';
    for (auto &x: ans) {
        cout << x + 1 << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
