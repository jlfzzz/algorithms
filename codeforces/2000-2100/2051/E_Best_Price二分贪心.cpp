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
    vector<int> b(n);
    For(i, n) cin >> b[i];

    int ans = 0;
    ranges::sort(a);
    ranges::sort(b);

    For(i, n) {
        auto calc = [&](int x) -> void {
            int buy = n - (ranges::lower_bound(b, x) - b.begin());
            int positve = n - (ranges::lower_bound(a, x) - a.begin());
            if (buy - positve <= k) {
                ans = max(ans, buy * x);
            }
        };
        calc(a[i]);
        calc(b[i]);
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
