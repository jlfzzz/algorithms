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
    int sum = accumulate(a.begin(), a.end(), 0ll);

    vector<int> b(2 * n);
    For(i, 2 * n) { b[i] = a[i % n]; }

    vector<int> pre(2 * n + 1);
    for (int i = 1; i <= 2 * n; i++) {
        pre[i] = pre[i - 1] + b[i - 1];
    }

    For(_, q) {
        int l, r;
        cin >> l >> r;

        l--, r--;

        int L = l / n, R = r / n;
        int ans = 0;

        l = l % n, r = r % n;
        if (L == R) {
            int s = pre[L + r + 1] - pre[l + L];
            ans += s;
        } else {
            ans = (R - L - 1) * sum;
            int s1 = pre[n + L] - pre[l + L];
            int s2 = pre[r + R + 1] - pre[R];
            ans += s1 + s2;
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
