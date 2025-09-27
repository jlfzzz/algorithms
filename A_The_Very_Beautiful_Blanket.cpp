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
    int n, m;
    cin >> n >> m;

    int shift = 10;

    cout << m * n << '\n';
    vector<vector<int>> ans(n, vector<int>(m));
    for (int i = 0; i < n; i += 2) {
        for (int j = 0; j < m; j++) {
            int t1, t2;
            int base = ((i >> 1) << shift) | j;
            if (j % 2 == 0) {
                t1 = (base << 2) | 0;
                t2 = (base << 2) | 3;
                ans[i][j] = t1;
                if (i + 1 < n)
                    ans[i + 1][j] = t2;
            } else {
                t1 = (base << 2) | 1;
                t2 = (base << 2) | 2;
                ans[i][j] = t1;
                if (i + 1 < n)
                    ans[i + 1][j] = t2;
            }
        }
    }

    For(i, n) {
        For(j, m) cout << ans[i][j] << ' ';
        cout << '\n';
    }
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
