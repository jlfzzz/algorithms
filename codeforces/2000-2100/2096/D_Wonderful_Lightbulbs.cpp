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

    map<int, int> cnt1, cnt2;
    For(i, n) {
        int x, y;
        cin >> x >> y;

        cnt1[x]++;
        cnt2[x + y]++;
    }

    int s = -1, t = -1;
    for (auto &[k, v]: cnt1) {
        if (v & 1) {
            s = k;
            break;
        }
    }

    for (auto &[k, v]: cnt2) {
        if (v & 1) {
            t = k - s;
            break;
        }
    }

    cout << s << ' ' << t << '\n';
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
