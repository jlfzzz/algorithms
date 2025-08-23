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
    int n;
    cin >> n;
    set<pii> points;
    For(i, n) {
        int x, y;
        cin >> x >> y;
        points.insert({x, y});
    }

    int ans = 0;
    for (auto it = points.begin(); it != points.end(); it++) {
        auto [x1, y1] = *it;
        if (next(it) != points.end()) {
            auto [x2, y2] = *next(it);
            if (x1 == x2) {
                ans += n - 2;
            }
        }

        if (y1 == 0) {
            if (points.contains({x1 + 1, 1}) && points.contains({x1 + 2, 0})) {
                ans++;
            }
        } else {
            if (points.contains({x1 + 1, 0}) && points.contains({x1 + 2, 1})) {
                ans++;
            }
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
