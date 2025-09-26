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
    int n, t;
    cin >> n >> t;
    vector<int> a(n), b(n);
    For(i, n) cin >> a[i];
    For(i, n) cin >> b[i];

    vector<pii> vp(n);
    For(i, n) { vp[i] = {a[i], b[i]}; }

    ranges::sort(vp, greater<>());
    int cnt = accumulate(a.begin(), a.end(), 0ll);
    int use = 0;
    for (int i = 0; i < n; i++) {
        if (cnt >= t) {
            break;
        }

        int need = t - cnt;
        auto [val, c] = vp[i];

        if (!val) {
            continue;
        }

        int tt = (need + val - 1) / val;


        use += min(tt, c);
        cnt += min(tt, c) * val;
    }

    if (cnt < t) {
        use = -1;
    }

    cout << use << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    while (T--)
        solve();
    return 0;
}
