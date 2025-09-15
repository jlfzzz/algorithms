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
    vector<char> lop(n + 1), rop(n + 1);
    vector<int> la(n + 1), ra(n + 1);
    for (int i = 1; i <= n; i += 1) {
        char c1, c2;
        int b1, b2;
        cin >> c1 >> b1 >> c2 >> b2;
        lop[i] = c1;
        la[i] = b1;
        rop[i] = c2;
        ra[i] = b2;
    }

    vector<array<int, 2>> f(n + 2);
    f[n + 1][0] = 1;
    f[n + 1][1] = 1;
    for (int i = n; i >= 1; i -= 1) {
        for (int j = 0; j < 2; j += 1) {
            char op = (j == 0 ? lop[i] : rop[i]);
            int a = (j == 0 ? la[i] : ra[i]);
            if (op == '+')
                f[i][j] = f[i + 1][j];
            else
                f[i][j] = f[i + 1][j] + (a - 1) * max(f[i + 1][0], f[i + 1][1]);
        }
    }

    int l = 1, r = 1;
    for (int i = 1; i <= n; i += 1) {
        int t1 = (lop[i] == '+') ? la[i] : (la[i] - 1) * l;
        int t2 = (rop[i] == '+') ? ra[i] : (ra[i] - 1) * r;
        int total= t1 + t2;
        if (f[i + 1][0] >= f[i + 1][1])
            l += total;
        else
            r += total;
    }

    cout << (l + r) << '\n';
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
