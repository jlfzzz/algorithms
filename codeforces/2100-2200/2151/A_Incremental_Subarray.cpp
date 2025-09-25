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
    vector<int> b(m);
    For(i, m) cin >> b[i];

    int ans = 0;
    bool f = false;
    for (int i = 1; i < m; i++) {
        if (b[i] <= b[i - 1]) {
            f = true;
            break;
        }
    }

    if (f) {
        ans = 1;
    } else {
        int last = b[m - 1];
        ans = n - last + 1;
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
