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
    int n, y;
    cin >> n >> y;
    vector<int> c(n + 1);
    For(i, n) cin >> c[i + 1];

    int mx = *max_element(c.begin(), c.end());

    vector<int> freq(mx + 1);
    for (int i = 1; i <= n; i++) {
        freq[c[i]]++;
    }

    vector<int> pre(mx + 1);
    for (int i = 1; i <= mx; i++) {
        pre[i] = pre[i - 1] + freq[i];
    }

    auto f = [&](int L, int R) -> int {
        if (L > R)
            return 0;
        if (L <= 1)
            return pre[R];
        return pre[R] - pre[L - 1];
    };

    int ans = -inf;
    for (int x = 2; x <= mx + 1; x++) {
        int k_mx = (mx + x - 1) / x;
        int cost = 0;
        int have = 0;

        for (int k = 1; k <= k_mx; k++) {
            int L = (k - 1) * x + 1;
            int R = min(k * x, mx);
            if (L > R)
                continue;

            int cnt = f(L, R);
            if (cnt == 0)
                continue;

            cost += cnt * k;
            int t = (k <= mx ? freq[k] : 0);
            if (cnt > t)
                have += (cnt - t);
        }

        int cur = cost - have * y;
        ans = max(ans, cur);
    }

    cout << ans << "\n";
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
