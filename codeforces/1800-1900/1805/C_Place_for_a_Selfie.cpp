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

    set<pii> lines;
    For(i, n) {
        int k;
        cin >> k;
        lines.insert({k, i + 1});
    }

    For(i, m) {
        int a, b, c;
        cin >> a >> b >> c;

        int rhs = 4 * a * c;
        if (rhs <= 0) {
            cout << "NO\n";
            continue;
        }

        auto it = lines.lower_bound({b, -1});

        auto ok = [&](int k) -> bool {
            i128 diff = (i128) b - (i128) k;
            i128 t = diff * diff;
            return t < (i128) rhs;
        };

        bool f = false;
        int ans = 0;
        if (it != lines.end() && ok(it->first)) {
            f = true;
            ans = it->first;
        } else if (it != lines.begin()) {
            auto it2 = prev(it);
            if (ok(it2->first)) {
                f = true;
                ans = it2->first;
            }
        }

        if (f) {
            cout << "YES\n" << ans << "\n";
        } else {
            cout << "NO\n";
        }
    }
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
