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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    vector<int> a(n);
    For(i, n) cin >> a[i];

    int ans = inf;
    int lo = 0, hi = ranges::max(a) + 1;

    while (lo < hi) {
        int m = lo + (hi - lo) / 2;

        auto check = [&](int limit) -> bool {
            int use = 0;
            char pre = 'R';

            for (int i = 0; i < n; i++) {
                int cost = a[i];
                if (cost > limit) {
                    if (s[i] == 'R') {
                        if (pre == 'B')
                            use++;
                        pre = 'R';
                    } else {
                        pre = 'B';
                    }
                }
            }
            if (pre == 'B') {
                use++;
            }
            return use <= k;
        };

        if (check(m)) {
            ans = m, hi = m;
        } else {
            lo = m + 1;
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
