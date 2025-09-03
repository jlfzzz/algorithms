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
    int n, x, y;
    cin >> n;
    string s;
    cin >> s;
    cin >> x >> y;

    int X = 0, Y = 0;
    for (char c: s) {
        if (c == 'U') {
            Y++;
        } else if (c == 'D') {
            Y--;
        } else if (c == 'L') {
            X--;
        } else {
            X++;
        }
    }

    int dx = X - x, dy = Y - y;

    int ans = inf;
    int l = 0;

    if (dx == 0 && dy == 0) {
        ans = 0;
    }

    int window_dx = 0, window_dy = 0;
    for (int r = 0; r < n; r++) {
        char c = s[r];
        if (c == 'U') {
            window_dy++;
        } else if (c == 'D') {
            window_dy--;
        } else if (c == 'L') {
            window_dx--;
        } else {
            window_dx++;
        }

        auto check = [&]() -> bool {
            int tx = dx - window_dx, ty = dy - window_dy;
            int cnt = r - l + 1;
            tx = abs(tx), ty = abs(ty);
            return (tx + ty == cnt) || (cnt >= tx + ty && (cnt - tx - ty) % 2 == 0);
        };

        while (check() && l <= r) {
            ans = min(ans, r - l + 1);
            char L = s[l];
            if (L == 'U') {
                window_dy--;
            } else if (L == 'D') {
                window_dy++;
            } else if (L == 'L') {
                window_dx++;
            } else {
                window_dx--;
            }
            l++;
        }
    }

    cout << (ans == inf ? -1 : ans) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
