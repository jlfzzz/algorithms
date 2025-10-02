#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    rd(n);
    vector<int> a(n + 1), b(n + 1);
    rd_vec(a, 1);
    rd_vec(b, 1);

    Z f1 = 1;
    Z f2 = 0;

    for (int i = 1; i <= n; i++) {
        Z n1 = 0, n2 = 0;
        if (a[i] >= a[i - 1] && b[i] >= b[i - 1])
            n1 += f1;
        if (a[i] >= b[i - 1] && b[i] >= a[i - 1])
            n1 += f2;
        if (b[i] >= a[i - 1] && a[i] >= b[i - 1])
            n2 += f1;
        if (b[i] >= b[i - 1] && a[i] >= a[i - 1])
            n2 += f2;
        f1 = n1;
        f2 = n2;
    }

    prt(f1.val() + f2.val());
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
