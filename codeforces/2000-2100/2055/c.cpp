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
    string s;
    cin >> s;

    vector<vector<int>> grid(n, vector<int>(m));
    For(i, n) {
        For(j, m) { cin >> grid[i][j]; }
    }

    vector<int> row_pre(n);
    vector<int> col_pre(m);
    For(i, n) {
        int t = 0;
        For(j, m) { t += grid[i][j]; }
        row_pre[i] = t;
    }

    For(i, m) {
        int t = 0;
        For(j, n) { t += grid[j][i]; }
        col_pre[i] = t;
    }

    int i = 0, j = 0;
    for (char c: s) {
        if (c == 'D') {
            grid[i][j] = -row_pre[i];
            col_pre[j] += grid[i][j];
            i++;
        } else {
            grid[i][j] = -col_pre[j];
            row_pre[i] += grid[i][j];
            j++;
        }
    }
    grid[n - 1][m - 1] = -row_pre[n - 1];

    For(i, n) {
        For(j, m) { cout << grid[i][j] << ' '; }
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
