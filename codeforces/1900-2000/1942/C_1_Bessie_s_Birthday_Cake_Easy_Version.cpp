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
    int n, x, y;
    cin >> n >> x >> y;
    int ans = x - 2;

    vector<int> v(x);
    For(i, x) cin >> v[i];

    ranges::sort(v);
    for (int i = 0; i < x - 1; i++) {
        int d = v[i + 1] - v[i];
        if (d == 2) {
            ans++;
        }
    }
    int d = v[0] + n - v.back();
    if (d == 2) {
        ans++;
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
