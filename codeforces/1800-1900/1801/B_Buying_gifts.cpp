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
    vector<int> b(n);
    vector<pii> a(n);

    For(i, n) {
        int x, y;
        cin >> x >> y;
        a[i] = {x, i}, b[i] = y;
    }

    int ans = inf;
    multiset<int> pre, suf;
    ranges::sort(a, greater<>());
    for (int x: b)
        suf.insert(x);

    for (int i = 0; i < n; i++) {
        auto [x, id] = a[i];
        suf.erase(suf.find(b[id]));

        int pre_mx = (!pre.empty()) ? *pre.rbegin() : -inf;
        if (pre_mx >= x) {
            ans = min(ans, abs(pre_mx - x));
        } else {
            if (pre_mx != -inf) {
                ans = min(ans, abs(pre_mx - x));
            }

            auto it = suf.lower_bound(x);
            if (it != suf.end()) {
                int t = *it;
                if (t > pre_mx) {
                    ans = min(ans, abs(t - x));
                }
            }

            if (it != suf.begin()) {
                it--;
                int t = *it;
                if (t > pre_mx) {
                    ans = min(ans, abs(t - x));
                }
            }
        }

        pre.insert(b[id]);
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
