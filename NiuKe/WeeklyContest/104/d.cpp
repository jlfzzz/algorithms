#include <bits/stdc++.h>
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
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    int origin = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            a[i][j] = x;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == min(i, j)) {
                origin++;
            }
        }
    }

    auto f = [&](int x1, int y1, int x2, int y2) -> int {
        int t1 = a[x1][y1], t2 = a[x2][y2];
        int before = 0;
        if (t1 == min(x1, y1)) {
            before++;
        }
        if (t2 == min(x2, y2)) {
            before++;
        }
        int after = 0;
        if (t1 == min(x2, y2)) {
            after++;
        }
        if (t2 == min(x1, y1)) {
            after++;
        }

        return after - before;
    };

    int ans = origin;
    for (int i1 = 1; i1 <= n; i1++) {
        for (int j1 = 1; j1 <= m; j1++) {
            if (a[i1][j1] == min(i1, j1)) {
                if (i1 < j1) {
                    for (int col = i1; col <= m; col++) {
                        if (col != j1) {
                            ans = max(ans, origin + f(i1, j1, i1, col));
                        }
                    }
                } else {
                    for (int row = j1; row <= n; row++) {
                        if (row != i1) {
                            ans = max(ans, origin + f(i1, j1, row, j1));
                        }
                    }
                }
            } else {
                int curr = a[i1][j1];
                if (curr <= m) {
                    for (int col = curr; col <= m; col++) {
                        if (col != j1) {
                            ans = max(ans, origin + f(i1, j1, curr, col));
                        }
                    }
                }
                if (curr <= n) {
                    for (int row = curr; row <= n; row++) {
                        if (row != i1) {
                            ans = max(ans, origin + f(i1, j1, row, curr));
                        }
                    }
                }
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
