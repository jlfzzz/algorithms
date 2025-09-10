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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    while (q--) {
        int k;
        cin >> k;
        int ans = 0;

        auto temp = a;

        for (int i = 62; i >= 0; i--) {
            i128 cost = 0;
            int mask = (1ll << i) - 1;
            int u = 1ll << i;
            vector<int> pos;
            for (int j = 0; j < n; j++) {
                int x = temp[j];
                if (x & (1ll << i)) {
                    continue;
                }
                int t = x & mask;
                cost += (i128)(u - t);
                pos.push_back(j);
            }

            if ((i128)k >= cost) {
                ans |= 1ll << i;
                for (int j: pos) {
                    temp[j] &= ~((1ll << i) - 1);
                }
                k -= (int)cost;
            }
        }

        cout << ans << '\n';
    }
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
