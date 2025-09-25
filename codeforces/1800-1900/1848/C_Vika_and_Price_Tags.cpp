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
    vector<int> a(n), b(n);
    For(i, n) cin >> a[i];
    For(i, n) cin >> b[i];

    auto f = [&](this auto &&f, int a, int b) -> int {
        int s = 0;
        while (true) {
            if (a == 0)
                return s % 3;
            if (b == 0)
                return (s + 1) % 3;
            if (a < b) {
                ++s;
                int na = b, nb = b - a;
                a = na;
                b = nb;
                continue;
            }
            if (a >= b * 2) {
                int m = (a - 2 * b) / (2 * b) + 1;
                a -= 2 * b * m;
                continue;
            } else {
                ++s;
                int na = b, nb = a - b;
                a = na;
                b = nb;
            }
        }
    };

    int pre = -1;
    For(i, n) {
        int x = a[i], y = b[i];
        if (x == 0 && y == 0) {
            continue;
        }
        int t = f(x, y);
        t %= 3;
        if (pre == -1) {
            pre = t;
        } else {
            if (t != pre) {
                cout << "NO\n";
                return;
            }
        }
    }

    cout << "YES" << '\n';
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
