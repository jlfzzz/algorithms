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
    vector<int> a(2 * n + 1);
    For(i, 2 * n) cin >> a[i + 1];

    int m = 2 * n - 1;
    vector<int> diff(m + 2, 0);
    for (int i = 1; i <= m; i++)
        diff[i] = a[i + 1] - a[i];

    vector<int> pre(m + 1, 0), pre2(m + 1, 0);
    vector<int> pre1(m + 1, 0), pre0(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        pre[i] = pre[i - 1] + diff[i];
        pre2[i] = pre2[i - 1] + i * diff[i];
        pre1[i] = pre1[i - 1] + ((i & 1) ? diff[i] : 0);
        pre0[i] = pre0[i - 1] + ((i & 1) ? 0 : diff[i]);
    }

    vector<int> suf(m + 3, 0), suf2(m + 3, 0);
    for (int i = m; i >= 1; i--) {
        suf[i] = suf[i + 1] + diff[i];
        suf2[i] = suf2[i + 1] + i * diff[i];
    }

    for (int k = 1; k <= n; k++) {
        int left = pre2[k - 1];

        int l = k, r = 2 * n - k - 1;
        int mid = 0;
        if (l <= r) {
            int sum = pre[r] - pre[l - 1];
            int t = (l & 1) ? (pre1[r] - pre1[l - 1]) : (pre0[r] - pre0[l - 1]);
            mid = (k - 1) * sum + t;
        }

        int L2 = 2 * n - k;
        int right = 0;
        if (L2 <= m) {
            right = (2 * n) * suf[L2] - suf2[L2];
        }

        int ans = left + mid + right;
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
