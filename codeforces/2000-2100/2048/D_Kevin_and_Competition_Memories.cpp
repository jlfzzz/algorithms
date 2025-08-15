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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> b(m);
    For(i, n) { cin >> a[i]; }
    For(i, m) cin >> b[i];

    int kevin = a[0];
    ranges::sort(a);

    vector<int> c(m);
    for (int i = 0; i < m; i++) {
        if (b[i] <= kevin) {
            c[i] = 1;
        } else {
            int can_solve = a.end() - (ranges::lower_bound(a, b[i]));
            c[i] = can_solve + 1;
        }
    }

    ranges::sort(c);
    for (int i = 1; i <= m; i++) {
        int ans = 0;
        for (int j = i - 1; j < m; j += i) {
            ans += c[j];
        }
        cout << ans << ' ';
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
