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
    int n, x;
    cin >> n >> x;

    set<int> vis;
    auto calc = [&](int target, int mn) -> int {
        int res = 0;
        for (int d = 1; d * d <= target; d++) {
            if (target % d == 0) {
                int D = d;
                if ((D & 1) == 0) {
                    int k = D / 2 + 1;
                    if (k >= mn && !vis.contains(k)) {
                        vis.insert(k);
                        res++;
                    }
                }
                int D2 = target / d;
                if (D2 != D && (D2 & 1) == 0) {
                    int k = D2 / 2 + 1;
                    if (k >= mn && !vis.contains(k)) {
                        vis.insert(k);
                        res++;
                    }
                }
            }
        }
        return res;
    };

    int ans = 0;
    ans += calc(n - x, x);
    if (x >= 2) {
        ans += calc(n + x - 2, x + 1);
    }
    cout << ans << '\n';
    // cout << "cnm" << endl;
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
