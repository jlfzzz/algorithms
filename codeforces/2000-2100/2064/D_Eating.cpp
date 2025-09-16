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
    int n, q;
    cin >> n >> q;

    vector<int> w(n);
    For(i, n) cin >> w[i];

    vector<set<int>> pos(35, set<int>());

    for (int i = 30; i >= 0; i--) {
        pos[i + 1] = pos[i + 2];
        int u = 1 << i;
        for (int j = 0; j < n; j++) {
            if (w[j] >= u) {
                pos[i + 1].insert(j);
            }
        }
    }

    vector<int> pre(n + 1);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] ^ w[i];
    }

    while (q--) {
        int x;
        cin >> x;

        int p = n - 1;

        while (true) {
            // cout << "x is: " << x << '\n';
            int bits = bit_width((ull) x);
            if (pos[bits].empty()) {
                // cout << "bits is: " << bits << ' ';
                cout << n << " ";
                break;
            }

            auto it = pos[bits].upper_bound(p);
            if (it == pos[bits].begin()) {
                cout << n << " ";
                break;
            }
            it--;
            int i = *it;
            int d = pre[p + 1] ^ pre[i + 1];

            // cout << "w is: " << w[i] << '\n';

            int t = d ^ x;
            if (t < w[i]) {
                cout << n - i - 1 << ' ';
                break;
            }

            x = t ^ w[i];
            p = i - 1;

            if (x == 0) {
                cout << n - p - 1 << ' ';
                break;
            }
        }
    }

    cout << '\n';
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
