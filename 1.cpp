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

void init() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    For(i, n) cin >> a[i];
    For(i, n) cin >> b[i];

    if (k >= accumulate(a.begin(), a.end(), 0ll)) {
        cout << 0 << '\n';
        return;
    }

    int lo = 1;
    int hi = n + 100;
    int ans = 1;

    while (lo < hi) {
        int mid = (lo + hi) / 2;

        auto check = [&](int target) -> int {
            int l = 0;
            int s1 = 0, s2 = 0;
            vector<int> mn(n, inf);
            int use = 0;
            for (int r = 0; r < 2 * n; r++) {
                int x = a[r % n], y = b[r % n];
                s1 += x, s2 += y;
                if (s1 > s2 && r - l + 1 > target) {
                    
                }
                while (s1 <= s2 && l <= r) {
                    mn[l % n] = min(r - l + 1, mn[l % n]);
                    s1 -= a[l % n];
                    s2 -= b[l % n];
                    l++;
                }
            }
        };
    }


    cout << ranges::max(mn) << '\n';
}

void solve() {}

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
