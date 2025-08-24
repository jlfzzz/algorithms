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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    For(i, n) cin >> a[i];
    vector<int> b(n);
    For(i, n) cin >> b[i];

    int sum = 0;
    For(i, n) { sum += min(a[i], b[i]); }

    For(_, q) {
        char c;
        int x, v;
        cin >> c >> x >> v;
        x--;

        if (c == 'A') {
            int old_a = a[x];
            int old_b = b[x];
            sum -= min(old_a, old_b);
            a[x] = v;
            sum += min(a[x], b[x]);
        } else {
            sum -= min(a[x], b[x]);
            b[x] = v;
            sum += min(a[x], b[x]);
        }
        cout << sum << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
