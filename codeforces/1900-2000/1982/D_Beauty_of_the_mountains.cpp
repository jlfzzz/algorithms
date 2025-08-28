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
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> grid(n, vector<int>(m));
    For(i, n) {
        For(j, m) { cin >> grid[i][j]; }
    }

    vector<vector<int>> diff1(n + 1, vector<int>(m + 1));
    int diff = 0;
    For(i, n) {
        string s;
        cin >> s;
        For(j, m) {
            if (s[j] == '0') {
                diff -= grid[i][j];
                diff1[i + 1][j + 1] = -1;
            } else {
                diff += grid[i][j];
                diff1[i + 1][j + 1] = 1;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            diff1[i][j] = diff1[i][j] + diff1[i - 1][j] + diff1[i][j - 1] - diff1[i - 1][j - 1];
        }
    }

    unordered_set<int> st;
    for (int i = 1; i + k - 1 <= n; i++) {
        for (int j = 1; j + k - 1 <= m; j++) {
            int t =
                diff1[i + k - 1][j + k - 1] - diff1[i + k - 1][j - 1] - diff1[i - 1][j + k - 1] + diff1[i - 1][j - 1];
            st.insert(t);
        }
    }

    int g = 0;
    for (auto v: st)
        g = gcd(g, llabs(v));
    if (g == 0) {
        cout << (diff == 0 ? "YES\n" : "NO\n");
    } else {
        cout << ((llabs(diff) % g == 0) ? "YES\n" : "NO\n");
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
