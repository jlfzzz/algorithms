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
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<int> pre(2 * n + 1);
    For(i, 2 * n) { pre[i + 1] = pre[i] + a[i % n]; }

    int first = 0;
    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int c;
            cin >> c;
            first = (first + c) % n;
        } else {
            int l, r;
            cin >> l >> r;

            int s = pre[first + r] - pre[first + l - 1];
            cout << s << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    while (T--)
        solve();
    return 0;
}
