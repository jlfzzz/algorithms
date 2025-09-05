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
    int h, w, x1, y1, x2, y2;
    cin >> h >> w >> x1 >> y1 >> x2 >> y2;

    if (x1 >= x2) {
        cout << "Draw\n";
        return;
    }
    int dx = x2 - x1;
    if (dx & 1) {
        int ta = dx / 2 + 1;
        int tb = dx / 2;
        int al = max(1ll, y1 - ta), ar = min(w, y1 + ta);
        int bl = max(1ll, y2 - tb), br = min(w, y2 + tb);
        if (al <= bl && br <= ar)
            cout << "Alice\n";
        else
            cout << "Draw\n";
    } else {
        int t = dx / 2;
        int al = max(1ll, y1 - t), ar = min(w, y1 + t);
        int bl = max(1ll, y2 - t), br = min(w, y2 + t);
        if (bl <= al && ar <= br)
            cout << "Bob\n";
        else
            cout << "Draw\n";
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
