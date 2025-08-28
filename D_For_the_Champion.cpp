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
constexpr int MOVE = 1000000000;
void solve() {
    int n;
    cin >> n;
    int d1 = LLONG_MIN, d2 = LLONG_MIN;
    For(i, n) {
        int x, y;
        cin >> x >> y;
        d1 = max(d1, x + y);
        d2 = max(d2, x - y);
    }

    auto f = [&](char c, int MOVE) -> int {
        cout << "? " << c << ' ' << MOVE << endl;
        int s;
        cin >> s;
        return s;
    };

    f('R', MOVE);
    f('R', MOVE);
    f('U', MOVE);
    int s1 = f('U', MOVE);

    f('D', MOVE);
    f('D', MOVE);
    f('D', MOVE);
    int s3 = f('D', MOVE);

    int a = s1 - 4 * MOVE + d1;
    int b = s3 - 4 * MOVE + d2;
    int x = (a + b) / 2;
    int y = (a - b) / 2;
    cout << "! " << x << ' ' << y << endl;
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
