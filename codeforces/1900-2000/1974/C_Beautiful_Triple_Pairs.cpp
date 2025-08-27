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
    map<tuple<int, int, int>, int> cnt1;
    map<pii, int> cnt2, cnt3, cnt4;

    int ans = 0;
    For(i, n - 2) {
        int x = a[i], y = a[i + 1], z = a[i + 2];
        ans += cnt2[{x, y}]++;
        ans += cnt3[{x, z}]++;
        ans += cnt4[{y, z}]++;
        ans -= 3 * cnt1[make_tuple(x, y, z)];
        cnt1[make_tuple(x, y, z)]++;
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
