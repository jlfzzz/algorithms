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
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    // cout << "cnmsl" << endl;
    vector<vector<int>> memo(n, vector<int>(17, -inf));
    auto dfs = [&](this auto &&dfs, int i, int mask) -> int {
        // cout << "cnmsl" << endl;
        if (i == n) {
            return 0;
        }

        int &x = memo[i][mask];
        if (x != -inf) {
            return x;
        }

        int pre = mask;
        if (mask == 16) {
            pre = (1 << 30) - 1;
        }

        int cur = a[i];
        cur = (cur + 1) / 2;

        int res = 1 + dfs(i + 1, 16);
        if (cur >= 16) {
            x = res;
            return x;
        }

        for (int j = 0; j < 16; j++) {
            int t = j;
            if (mask != 16) {
                t |= pre;
            }
            int t2 = (1 << cur) - 1;
            t2 &= t;
            if (t2 != (1 << cur) - 1) {
                continue;
            }

            res = min(res, popcount((ull) j) + dfs(i + 1, j));
        }

        x = res;
        return res;
    };

    int ans = dfs(0, 0);
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
