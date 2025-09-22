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
    int n;
    cin >> n;

    vector<int> a(n);
    For(i, n) cin >> a[i];

    map<int, int> cnt;
    for (int x: a) {
        cnt[x]++;
    }

    int m = cnt.size();
    vector<int> temp(m);
    auto it = cnt.begin();
    for (int i = 0; i < m; i++) {
        temp[i] = it->second;
        it++;
    }

    vector<vector<int>> memo(m, vector<int>(m, -inf));

    auto dfs = [&](this auto &&dfs, int i, int j) -> int {
        if (i == m) {
            return 0;
        }

        int &x = memo[i][j];
        if (x != -inf) {
            return x;
        }

        int res = 1 + dfs(i + 1, j + 1);

        if (j >= temp[i]) {
            res = min(res, dfs(i + 1, j - temp[i]));
        }

        return x = res;
    };

    int ans = dfs(0, 0);
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
