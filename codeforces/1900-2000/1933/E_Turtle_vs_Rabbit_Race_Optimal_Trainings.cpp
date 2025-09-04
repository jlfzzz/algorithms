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
    vector<int> pre(n + 1);
    For(i, n) pre[i + 1] = pre[i] + a[i];

    int q;
    cin >> q;
    while (q--) {
        int l, u;
        cin >> l >> u;

        int curr = pre[l - 1];
        int R = u + curr;
        int i = ranges::lower_bound(pre, R) - pre.begin();
        if (i == n + 1) {
            i = n;
        }
        int sum = pre[i] - curr;
        int L = u - sum + 1;

        int ans1 = (L + u) * sum / 2;
        sum = pre[i - 1] - curr;
        L = u - sum + 1;
        if (i != 1 && ((L + u) * sum / 2) >= ans1 && i >= l + 1) {
            i--;
        }

        cout << i << ' ';
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
