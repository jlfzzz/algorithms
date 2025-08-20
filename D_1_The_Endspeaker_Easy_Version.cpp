#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int (i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {
    
}

void solve() { int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];
    vector<int> b(m + 1);
    For(i, m) cin >> b[i + 1];

    if (ranges::max(a) > ranges::max(b)) {
        cout << -1 << '\n';
        return;
    }

    vector<int> suf_max(n + 1, -inf);
    suf_max[n] = a[n];
    for (int i = n - 1; i >= 1;i--) {
        suf_max[i] = max(suf_max[i + 1], a[i]);
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, inf));
    for (int i = 0; i <= m; i++) {
        dp[1][i] = 0;
    }
    vector<int> pre_sum(n + 1);
    for (int i = 1; i <= n;i++){
        pre_sum[i] = pre_sum[i - 1] + a[i];
    }

    for (int i = 1; i <= n;i++) {
        for (int j = 1; j <= m; j++) {
            if (dp[i][j] == inf) {
                continue;
            }

            
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}