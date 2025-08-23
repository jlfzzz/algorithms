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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    string s;
    cin >> s;
    s = ' ' + s;

    int cnt0 = 0, cnt1 = 0, cnt2 = 0;
    int cnt = 0;
    auto dfs = [&](this auto &&dfs, int i, int fa) -> void {
        if (i != 1 && g[i].size() == 1) {
            char c = s[i];
            if (c == '?') {
                cnt2++;
            } else if (c == '0') {
                cnt0++;
            } else {
                cnt1++;
            }
        }

        if (s[i] == '?' && i != 1) {
            cnt++;
        }

        for (int v: g[i]) {
            if (v == fa) {
                continue;
            }

            dfs(v, i);
        }
    };
    dfs(1, -1);

    int ans = 0;
    if (s[1] != '?') {
        int root = s[1] - '0';
        if (root) {
            ans = cnt0 + (cnt2 + 1) / 2;
        } else {
            ans = cnt1 + (cnt2 + 1) / 2;
        }
    } else {
        int t = cnt - cnt2;
        if (cnt0 == cnt1) {
            if (t & 1) {
                ans = cnt0 + (cnt2 + 1) / 2;
            } else {
                ans = cnt0 + cnt2 / 2;
            }
        } else {
            ans = max(cnt1, cnt0) + cnt2 / 2;
        }
    }
    cout << ans << '\n';
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
