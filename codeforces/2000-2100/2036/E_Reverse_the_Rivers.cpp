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
    int n, k, q;
    cin >> n >> k >> q;

    vector<vector<int>> values(n, vector<int>(k));
    For(i, n) {
        For(j, k) { cin >> values[i][j]; }
    }

    for (int i = 0; i < k; i++) {
        for (int j = 1; j < n; j++) {
            values[j][i] |= values[j - 1][i];
        }
    }

    vector<vector<int>> columns(k, vector<int>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            columns[i][j] = values[j][i];
        }
    }

    For(i, q) {
        int m;
        cin >> m;
        int lo = 0, hi = n - 1;
        For(j, m) {
            int r, c;
            char o;
            cin >> r >> o >> c;

            if (o == '>') {
                int t = ranges::upper_bound(columns[r - 1], c) - columns[r - 1].begin();
                lo = max(t, lo);
            } else {
                int t = ranges::lower_bound(columns[r - 1], c) - columns[r - 1].begin();
                hi = min(hi, t - 1);
            }
        }

        if (lo <= hi) {
            cout << lo + 1 << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
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
