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

    auto ask = [&](int a, int b, int c, int d) -> int {
        cout << "? " << a << ' ' << b << ' ' << c << ' ' << d << endl;
        char t;
        cin >> t;
        if (t == '<') {
            return -1;
        } else if (t == '=') {
            return 0;
        } else {
            return 1;
        }
    };

    int mx = 0;
    for (int i = 1; i < n; i++) {
        int t = ask(mx, mx, i, i);
        if (t < 0) {
            mx = i;
        }
    }

    int best = -1;
    vector<int> cand;
    for (int i = 0; i < n; i++)
        if (i != mx) {
            if (best == -1) {
                best = i;
                cand = {i};
            } else {
                int t = ask(i, mx, best, mx);
                if (t > 0) {
                    best = i;
                    cand.clear();
                    cand.push_back(i);
                } else if (t == 0) {
                    cand.push_back(i);
                }
            }
        }

    int mn = cand[0];
    for (int idx = 1; idx < (int) cand.size(); idx++) {
        int y = cand[idx];
        int t = ask(mn, mn, y, y);
        if (t > 0)
            mn = y;
    }

    cout << "! " << mx << ' ' << mn << endl;
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
