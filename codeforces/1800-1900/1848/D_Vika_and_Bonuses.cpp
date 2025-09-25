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
    int s, k;
    cin >> s >> k;

    if (s % 10 == 0) {
        cout << s * k << '\n';
        return;
    }

    if (s % 10 == 5) {
        int s1 = s * k;
        int s2 = (s + 5) * (k - 1);
        cout << max(s1, s2) << '\n';
        return;
    }

    int ans = s * k;

    int cur_s = s;
    int cur_k = k;
    int lim = min<int>(k, 20);
    for (int t = 1; t <= lim; t++) {
        cur_s += cur_s % 10;
        cur_k -= 1;
        ans = max(ans, cur_s * cur_k);
    }

    if (cur_k > 0) {
        auto eval = [&](int m) -> int {
            int s2 = cur_s + 20 * m;
            int k2 = cur_k - 4 * m;
            int best = s2 * k2;
            int s3 = s2;
            for (int extra = 1; extra <= 3 && k2 - extra >= 0; extra++) {
                s3 += s3 % 10;
                best = max(best, s3 * (k2 - extra));
            }
            return best;
        };

        long double est = ((long double) cur_k - (long double) cur_s / 5.0L) / 8.0L;
        int m_center = (int) floor(est);
        int m_lo = max<int>(0, m_center - 5);
        int m_hi = min<int>(cur_k / 4, m_center + 5);

        ans = max(ans, eval(0));
        ans = max(ans, eval(cur_k / 4));
        for (int m = m_lo; m <= m_hi; m++) {
            ans = max(ans, eval(m));
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
