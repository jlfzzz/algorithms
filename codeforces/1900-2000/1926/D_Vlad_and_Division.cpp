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
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int ans = 0;
    int mask = (1ll << 31) - 1;
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        if (cnt.contains(mask - x)) {
            cnt[mask - x]--;
            ans++;
        } else {
            cnt[x]++;
        }
    }

    for (auto &[k, v]: cnt) {
        ans += v;
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
