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
    int n, m;
    cin >> n >> m;
    map<int, int> mp;
    For(i, n) {
        int a;
        cin >> a;
        mp[a]++;
    }

    int ans = 0;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        auto [val1, cnt1] = *it;
        ans = max(ans, min(m / val1, cnt1) * val1);
        if (next(it) == mp.end()) {
            break;
        }
        auto [val2, cnt2] = *(next(it));
        if (val1 + 1 == val2) {
            int choose1 = min(m / val1, cnt1);
            int rem = m - choose1 * val1;
            int choose2 = min(cnt2, rem / val2);
            rem -= choose2 * val2;
            int extra = min({choose1, cnt2 - choose2, rem});
            rem -= extra;
            ans = max(ans, m - rem);
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
