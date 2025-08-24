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
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];

    map<int, vector<int>> mp;
    for (int i = 1; i <= n; i++) {
        mp[a[i] + i - 1].push_back(i);
    }

    unordered_set<int> vis;
    int ans = n;

    auto dfs = [&](this auto &&dfs, int i) -> void {
        if (vis.contains(i)) {
            return;
        }
        vis.insert(i);

        ans = max(ans, i);
        if (!mp.contains(i)) {
            return;
        }

        for (int v: mp[i]) {
            dfs(i + v - 1);
        }
    };

    dfs(n);
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
