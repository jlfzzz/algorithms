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
    vector<int> b(n);
    For(i, n) cin >> b[i];

    int cnt = 0;
    int cnt1 = 0;
    int cnt2 = 0;
    int neg = 0;

    for (int i = 0; i < n; i++) {
        int x = a[i], y = b[i];

        if (x == -1) {
            if (y == -1) {
                neg++;
            } else if (y == 0) {

            } else {
                cnt2++;
            }
        } else if (x == 0) {
            if (y == -1) {
            } else if (y == 0) {
            } else {
                cnt2++;
            }
        } else {
            if (y == -1) {
                cnt1++;
            } else if (y == 0) {
                cnt1++;
            } else {
                cnt++;
            }
        }
    }

    if (cnt1 > cnt2) {
        int d = cnt1 - cnt2;
        cnt1 -= min(d, neg);
        neg -= min(d, neg);
    } else {
        int d = cnt2 - cnt1;
        cnt2 -= min(d, neg);
        neg -= min(d, neg);
    }

    neg -= cnt;
    if (neg > 0) {
        while (neg--) {
            if (cnt1 > cnt2) {
                cnt1--;
            } else {
                cnt2--;
            }
        }
    } else {
        while (neg++) {
            if (cnt1 < cnt2) {
                cnt1++;
            } else {
                cnt2++;
            }
        }
    }

    cout << min(cnt1, cnt2) << '\n';
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
