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
    int n, k;
    cin >> n >> k;

    vector<int> colors(n + 1);

    map<int, vector<int>> groups;
    For(i, n) {
        int c;
        cin >> c;
        colors[i + 1] = c;
        groups[c].push_back(i + 1);
    }

    int ans = inf;

    for (auto &[_, v]: groups) {
        int mx = v[0] - 1;
        int mx2 = 0;
        for (int i = 1; i < v.size(); i++) {
            int d = v[i] - v[i - 1] - 1;
            if (d > mx) {
                mx2 = mx;
                mx = d;
            } else if (d > mx2) {
                mx2 = d;
            }
        }

        int d = n - v[v.size() - 1];
        if (d > mx) {
            mx2 = mx;
            mx = d;
        } else if (d > mx2) {
            mx2 = d;
        }

        ans = min(ans, max(mx2, mx / 2));
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
