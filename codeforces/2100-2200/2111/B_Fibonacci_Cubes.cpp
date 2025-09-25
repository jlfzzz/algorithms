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

    vector<int> len(n);
    len[0] = 1;
    len[1] = 2;
    for (int i = 2; i < n; i++) {
        len[i] = len[i - 1] + len[i - 2];
    }

    int height = len[n - 1] + len[n - 2];
    int L = len[n - 1];
    int height2 = len[n - 1];
    int L2 = len[n - 1] + len[n - 2];

    string ans;
    For(i, m) {
        int w, l, h;
        cin >> w >> l >> h;

        bool f = false;
        if (h >= height && w >= L && l >= L) {
            f = true;
        }

        if (h >= height2 && ((w >= L2 && l >= L) || (l >= L2 && w >= L))) {
            f = true;
        }

        if (f) {
            ans += '1';
        } else {
            ans += '0';
        }
    }

    cout << ans << '\n';
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
