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
    For(i, n) {
        string s;
        cin >> s;
        For(j, m) { grid[i][j] = s[j] - '0'; }
    }

    vector<vector<int>> t;
    for (int i = 0; i < min(n, m) / 2; i++) {
        vector<int> temp;
        for (int j = i; j < m - i; j++) {
            temp.push_back(grid[i][j]);
        }
        for (int j = i + 1; j < n - i - 1; j++) {
            temp.push_back(grid[j][m - 1 - i]);
        }
        for (int j = m - i - 1; j >= i; j--) {
            temp.push_back(grid[n - 1 - i][j]);
        }
        for (int j = n - i - 2; j > i; j--) {
            temp.push_back(grid[j][i]);
        }
        t.emplace_back(temp);
    }

    int ans = 0;
    for (auto &v: t) {
        int sz = v.size();
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == 1 and v[(i + 1) % sz] == 5 and v[(i + 2) % sz] == 4 and v[(i + 3) % sz] == 3) {
                ans++;
            }
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
