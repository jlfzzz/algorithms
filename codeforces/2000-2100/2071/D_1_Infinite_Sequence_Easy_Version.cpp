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
    int n, l, r;
    cin >> n >> l >> r;

    vector<int> a(n + 2);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    vector<int> pre(n + 2, 0);
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] ^ a[i];
    int s = pre[n];
    if ((n & 1) == 0) {
        int an1 = pre[n / 2];
        a[++n] = an1;
        s ^= an1;
        pre[n] = s;
    }

    function<int(int)> get = [&](int x) -> int {
        if (x <= n)
            return a[x];
        if (x <= 2 * n) {
            return pre[x / 2];
        }
        int m = x / 2;
        if ((m & 1) == 1)
            return s;
        return s ^ get(m);
    };

    cout << get(l) << '\n';
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
