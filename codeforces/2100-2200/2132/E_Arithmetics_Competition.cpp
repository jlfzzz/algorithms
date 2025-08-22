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
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> a(n), b(m);
    For(i, n) cin >> a[i];
    For(i, m) cin >> b[i];

    ranges::sort(a);
    ranges::sort(b);
    ranges::reverse(a);
    ranges::reverse(b);

    vector<int> preA(n + 1, 0), preB(m + 1, 0);
    for (int i = 0; i < n; ++i)
        preA[i + 1] = preA[i] + a[i];
    for (int i = 0; i < m; ++i)
        preB[i + 1] = preB[i] + b[i];

    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;

        int L = max(0ll, z - y);
        int R = min(x, z);
        if (L > R) {
            cout << 0 << '\n';
            continue;
        }

        int lo = L, hi = R;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (mid == 0) {
                hi = mid - 1;
                continue;
            }
            int idxB = z - mid;
            bool cond;
            if (idxB >= m) {
                cond = true;
            } else if (idxB < 0) {
                cond = true;
            } else {
                cond = (a[mid - 1] >= b[idxB]);
            }

            if (cond)
                lo = mid;
            else
                hi = mid - 1;
        }

        long long ans = -inf;
        for (int t = -1; t <= 1; ++t) {
            int k = lo + t;
            if (k < L || k > R)
                continue;
            int tt = z - k;
            if (tt < 0 || tt > m)
                continue;
            ans = max(ans, preA[k] + preB[tt]);
        }
        cout << ans << '\n';
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
