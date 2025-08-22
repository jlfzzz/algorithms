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
    int n, m;
    cin >> n >> m;
    vector grid(n, vector<int>(m));
    For(i, n) { For(j, m) cin >> grid[i][j]; }

    For(i, n) {
        For(j, m) {
            int curr = grid[i][j];
            bool f = true;
            int mx = -inf;
            if (i - 1 >= 0) {
                int t = grid[i - 1][j];
                if (curr <= t) {
                    f = false;
                } else {
                    mx = max(mx, t);
                }
            }

            if (i + 1 < n) {
                int t = grid[i + 1][j];
                if (curr <= t) {
                    f = false;
                } else {
                    mx = max(mx, t);
                }
            }

            if (j - 1 >= 0) {
                int t = grid[i][j - 1];
                if (curr <= t) {
                    f = false;
                } else {
                    mx = max(mx, t);
                }
            }

            if (j + 1 < m) {
                int t = grid[i][j + 1];
                if (curr <= t) {
                    f = false;
                } else {
                    mx = max(mx, t);
                }
            }

            if (f) {
                grid[i][j] = mx;
            }
        }
    }

    For(i, n) {
        For(j, m) cout << grid[i][j] << ' ';
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
