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

int pow2[30];

void init() {
    pow2[0] = 1;
    for (int i = 1; i < 30; i++) {
        pow2[i] = 2 * pow2[i - 1];
    }
}

void solve() {
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;

    auto dfs = [&](this auto &&dfs, int l1, int r1, int l2, int r2) -> int {
        if (l1 >= r1 || l2 >= r2)
            return 0;
        int lim = min(r1 - l1, r2 - l2);
        int res = 0;
        for (int i = 29; i >= 0; i--) {
            int p = pow2[i];
            if (p > lim)
                continue;
            int L1 = l1 + ((p - (l1 % p)) % p);
            int L2 = l2 + ((p - (l2 % p)) % p);
            int last1 = r1 - p;
            int last2 = r2 - p;
            if (L1 <= last1 && L2 <= last2) {
                int c1 = (last1 - L1) / p + 1;
                int c2 = (last2 - L2) / p + 1;
                res = c1 * c2;
                res += dfs(l1, L1, l2, r2);
                res += dfs(L1 + p * c1, r1, l2, r2);
                res += dfs(L1, L1 + p * c1, l2, L2);
                res += dfs(L1, L1 + p * c1, L2 + p * c2, r2);
                break;
            }
        }
        return res;
    };

    int ans = dfs(l1, r1, l2, r2);

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
