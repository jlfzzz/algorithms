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
    int n, m;
    cin >> n >> m;

    auto ask = [&](int x, int y) -> int {
        cout << "? " << x << ' ' << y << endl;
        int t;
        cin >> t;
        return t;
    };

    int d1 = ask(1, 1);
    int d2 = ask(n, 1);
    int d3 = ask(1, m);


    int y1 = 1 + (d1 + d2 - n + 1) / 2;
    int x1 = 1 + (d1 - (y1 - 1));

    if (x1 >= 1 && x1 <= n && y1 >= 1 && y1 <= m) {
        int t = ask(x1, y1);
        if (t == 0) {
            cout << "! " << x1 << ' ' << y1 << endl;
            return;
        }
    }

    int x2 = 1 + (d1 + d3 - m + 1) / 2;
    int y2 = 1 + (d1 - (x2 - 1));

    cout << "! " << x2 << ' ' << y2 << endl;
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
