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
    vector<int> p(n + 1);
    For(i, n) cin >> p[i + 1];

    vector<int> have(n + 1);
    for (int i = 1; i <= n; i++) {
        if (p[i] != 0)
            have[p[i]] = 1;
    }

    vector<int> missing;
    for (int v = 1; v <= n; v++)
        if (!have[v])
            missing.push_back(v);

    vector<int> zeros;
    int l0 = -1, r0 = -1;
    for (int i = 1; i <= n; i++) {
        if (p[i] == 0) {
            zeros.push_back(i);
        } else if (p[i] != i) {
            if (l0 == -1)
                l0 = i;
            r0 = i;
        }
    }

    int k = zeros.size();
    int ans = 0;

    if (k == 0) {
        if (l0 == -1)
            ans = 0;
        else
            ans = r0 - l0 + 1;
    } else if (k >= 2) {
        int mn = *min_element(zeros.begin(), zeros.end());
        int mx = *max_element(zeros.begin(), zeros.end());
        int l = (l0 == -1 ? mn : min(l0, mn));
        int r = (r0 == -1 ? mx : max(r0, mx));
        ans = r - l + 1;
    } else {
        int z = zeros[0];
        int m = missing[0];
        if (z == m) {
            if (l0 == -1)
                ans = 0;
            else
                ans = r0 - l0 + 1;
        } else {
            int l = (l0 == -1 ? z : min(l0, z));
            int r = (r0 == -1 ? z : max(r0, z));
            ans = r - l + 1;
        }
    }

    cout << ans << '\n';

    // int ans = 0;
    // if (mx == -1) {
    //     int p1 = -1;
    //     for (int i = 1; i <= n; i++) {
    //         if (p[i] != i) {
    //             p1 = i;
    //             break;
    //         }
    //     }

    //     int p2 = -1;
    //     for (int i = n; i >= 1; i--) {
    //         if (p[i] != i) {
    //             p2 = i;
    //             break;
    //         }
    //     }

    //     if (p1 == -1) {
    //         ans = 0;
    //     } else {
    //         ans = p2 - p1 + 1;
    //     }
    // } else {
    //     int mn = -1;
    //     for (int i = 1; i <= n; i++) {
    //         if (p[i] == 0) {
    //             mx = i;
    //             break;
    //         }
    //     }

    //     ans = mx - mn + 1;
    // }

    // cout << ans << '\n';
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
