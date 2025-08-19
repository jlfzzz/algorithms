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
    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<int> left_mx(n);
    left_mx[0] = a[0];
    int mx = a[0];
    for (int i = 1; i < n; i++) {
        mx = max(mx, a[i]);
        left_mx[i] = mx;
    }

    set<pii> right_mn;
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {
        int l_mx = left_mx[i];
        int x = a[i];
        a[i] = max(a[i], l_mx);
        auto it = right_mn.lower_bound({a[i], -1});
        if (it != right_mn.begin()) {
            it--;
            auto [mn, j] = *it;
            a[i] = max(a[i], left_mx[j]);
        }
        right_mn.emplace(x, i);
        left_mx[i] = max(l_mx, a[i]);
    }
    for (int x: a) {
        cout << x << ' ';
    }
    cout << '\n';
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
