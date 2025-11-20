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

    vector<vector<char>> grid(n + 1, vector<char>(m + 1));

    For(i, n) {
        string s;
        cin >> s;
        For(j, m) { grid[i + 1][j + 1] = s[j]; }
    }

    vector<vector<int>> heights(n + 1, vector<int>(m + 1));
    vector<vector<int>> cnt(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] != '#') {
                heights[i][j] = heights[i - 1][j] + 1;
            } else {
                heights[i][j] = 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i * j <= k) {
                cnt[i][j] = 1;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cnt[i][j] = cnt[i][j] + 2 * cnt[i][j - 1];
            if (j >= 2) {
                cnt[i][j] -= cnt[i][j - 2];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cnt[i][j] += cnt[i - 1][j];
        }
    }

    auto cal = [&](int k, int x, int y) {
        if (x + y + 1 > m)
            return 0LL;
        return cnt[k][x + y + 1] - cnt[k][x] - cnt[k][y];
    };

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        vector<int> L(m + 1), R(m + 1);
        stack<int> st;

        for (int j = 1; j <= m; j++) {
            while (!st.empty() && heights[i][j] <= heights[i][st.top()]) {
                st.pop();
            }
            if (st.empty()) {
                L[j] = 1;
            } else {
                L[j] = st.top() + 1;
            }
            st.push(j);
        }

        while (!st.empty())
            st.pop();

        for (int j = m; j >= 1; j--) {
            while (!st.empty() && heights[i][j] < heights[i][st.top()]) {
                st.pop();
            }
            if (st.empty()) {
                R[j] = m;
            } else {
                R[j] = st.top() - 1;
            }
            st.push(j);
        }

        for (int j = 1; j <= m; j++) {
            if (heights[i][j] == 0)
                continue;

            int h = heights[i][j];
            int left_len = j - L[j];
            int right_len = R[j] - j;

            ans += cal(h, left_len, right_len);
        }
    }

    cout << ans << '\n';
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
