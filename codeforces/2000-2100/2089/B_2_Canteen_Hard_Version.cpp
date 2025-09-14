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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    For(i, n) cin >> a[i];
    For(i, n) cin >> b[i];

    int lo = 0, hi = n + 10;
    int ans = 0;
    while (lo < hi) {
        int mid = (lo + hi) / 2;

        auto check = [&](int lim) -> bool {
            int use = 0;
            auto ta = a, tb = b;

            vector<int> stk;

            for (int i = 0; i < 2 * n; i++) {
                stk.push_back(i);
                while (!stk.empty() && tb[i % n]) {
                    int j = stk.back();
                    if (i - j + 1 > lim) {
                        use += ta[j % n];
                        ta[j % n] = 0;
                        stk.pop_back();
                    } else {
                        int mn = min(ta[j % n], tb[i % n]);
                        ta[j % n] -= mn;
                        tb[i % n] -= mn;

                        if (ta[j % n] == 0) {
                            stk.pop_back();
                        }
                    }
                }
            }

            return use <= k;
        };

        if (check(mid)) {
            ans = mid;
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

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
