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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int sum = accumulate(a.begin(), a.end(), 0ll);
    int mx = ranges::max(a);

    for (int i = n; i >= 1; i--) {
        if ((sum + k) / i < mx) {
            continue;
        }

        if ((sum + k) / i * i < sum) {
            continue;
        }

        cout << i << '\n';
        return;
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
