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
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n), d(m), f(k);
    For(i, n) cin >> a[i];
    For(i, m) cin >> d[i];
    For(i, k) cin >> f[i];

    sort(d.begin(), d.end());
    sort(f.begin(), f.end());

    auto check = [&](int t) -> bool {
        int cb = 0;
        int L = 0, R = 0;
        for (int i = 0; i + 1 < n; i++) {
            int diff = a[i + 1] - a[i];
            if (diff > t) {
                cb++;
                if (cb > 1)
                    return false;
                L = a[i];
                R = a[i + 1];
            }
        }
        if (cb == 0)
            return true;

        int loX = R - t;
        int hiX = L + t;
        if (loX > hiX)
            return false;

        int i = 0, j = f.size() - 1;
        while (i < d.size() && j >= 0) {
            int s = d[i] + f[j];
            if (s < loX) {
                i++;
            } else if (s > hiX) {
                j--;
            } else {
                return true;
            }
        }
        return false;
    };

    int lo = 0, hi = 2e9 + 5;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (check(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    cout << lo << "\n";
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
