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
    int n, m, v, e;
    cin >> n >> m >> v >> e;

    vector<int> rooms1(n + 1), rooms2(n + 1);
    For(i, n) cin >> rooms1[i + 1];
    For(i, n) cin >> rooms2[i + 1];

    vector<double> prob(n + 1);
    For(i, n) cin >> prob[i + 1];

    vector<vector<int>> g(v + 1, vector<int>(v + 1, inf));
    for (int i = 1; i <= v; i++)
        g[i][i] = 0;
    For(i, e) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a][b] = min(g[a][b], w);
        g[b][a] = min(g[b][a], w);
    }

    for (int k = 1; k <= v; k++)
        for (int i = 1; i <= v; i++)
            for (int j = 1; j <= v; j++)
                if (g[i][k] + g[k][j] < g[i][j])
                    g[i][j] = g[i][k] + g[k][j];

    vector<vector<double>> dp1(n + 1, vector<double>(m + 1, 1e100));
    vector<vector<double>> dp2(n + 1, vector<double>(m + 1, 1e100));
    dp1[1][0] = 0;
    if (m >= 1)
        dp2[1][1] = 0;

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= min<ll>(m, i); j++) {
            int c_pre = rooms1[i - 1], d_pre = rooms2[i - 1];
            int c_cur = rooms1[i], d_cur = rooms2[i];
            double p_pre = prob[i - 1], p_cur = prob[i];

            double dist_cc = (double) g[c_pre][c_cur];
            double dist_dc = (double) g[d_pre][c_cur];
            double dist_cd = (double) g[c_pre][d_cur];
            double dist_dd = (double) g[d_pre][d_cur];

            if (j <= i - 1) {
                dp1[i][j] = min(dp1[i][j], dp1[i - 1][j] + dist_cc);
                dp1[i][j] = min(dp1[i][j], dp2[i - 1][j] + p_pre * dist_dc + (1.0 - p_pre) * dist_cc);
            }

            if (j >= 1) {
                dp2[i][j] = min(dp2[i][j], dp1[i - 1][j - 1] + p_cur * dist_cd + (1.0 - p_cur) * dist_cc);
                dp2[i][j] =
                    min(dp2[i][j], dp2[i - 1][j - 1] + p_pre * p_cur * dist_dd + p_pre * (1.0 - p_cur) * dist_dc +
                                       (1.0 - p_pre) * p_cur * dist_cd + (1.0 - p_pre) * (1.0 - p_cur) * dist_cc);
            }
        }
    }

    double ans = 1e100;
    for (int j = 0; j <= m; j++) {
        ans = min(ans, dp1[n][j]);
        ans = min(ans, dp2[n][j]);
    }

    cout.setf(std::ios::fixed);
    cout << setprecision(2) << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    //  cin >> T;
    while (T--)
        solve();
    return 0;
}
