#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> pos(n);
    For(i, n) cin >> pos[i];

    ranges::sort(pos);
    int ans = 0;
    if (-pos[0] > pos[n - 1]) {
        int j = ranges::lower_bound(pos, 0) - pos.begin();
        for (int i = k; i < j; i += k) {
            ans += -pos[i] * 2;
        }
        ans += -pos[0];
        for (int i = n - 1; i >= j; i -= k) {
            ans += pos[i] * 2;
        }
    } else {
        int j = ranges::lower_bound(pos, 0) - pos.begin();
        for (int i = n - k - 1; i >= j; i -= k) {
            ans += pos[i] * 2;
        }
        ans += pos[n - 1];
        for (int i = 0; i < j; i += k) {
            ans += -pos[i] * 2;
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
