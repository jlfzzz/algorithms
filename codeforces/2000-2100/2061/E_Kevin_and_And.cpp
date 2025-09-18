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

    vector<int> a(n + 1);
    vector<int> b(m);
    For(i, n) cin >> a[i + 1];
    For(i, m) cin >> b[i];

    int u = 1 << m;
    vector<int> val(u + 1), pc(u + 1);
    for (int i = 0; i < u; i++) {
        int mask = (1 << 30) - 1;
        for (int j = 0; j < m; j++) {
            if (i >> j & 1) {
                mask &= b[j];
            }
        }
        val[i] = mask;
        pc[i] = popcount((ull) i);
    }

    vector<int> total;
    for (int i = 1; i <= n; i++) {
        int x = a[i];
        vector<int> temp(m + 1, x);
        for (int j = 1; j < u; j++) {
            int c1 = pc[j];
            if ((x & val[j]) < temp[c1]) {
                temp[c1] = x & val[j];
            }
        }

        for (int j = 1; j <= m; j++) {
            total.push_back(temp[j - 1] - temp[j]);
        }
    }

    ranges::sort(total);
    ranges::reverse(total);
    int cnt = 0;
    For(i, k) { cnt += total[i]; }

    int ans = accumulate(a.begin(), a.end(), 0ll) - cnt;
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
