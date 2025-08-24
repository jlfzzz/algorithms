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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;

    int mx = 0;
    unordered_map<int, vector<int>> cnt;
    for (int i = 1; i <= n; i++) {
        cout << "? " << i << ' ' << n << ' ';
        for (int j = 1; j <= n; j++) {
            // if (i == j) {
            //     continue;
            // }
            cout << j << ' ';
        }
        cout << endl;

        int t;
        cin >> t;
        mx = max(mx, t);
        cnt[t].push_back(i);
    }

    int start = cnt[mx][0];
    vector<int> ans;
    ans.push_back(start);
    for (int i = mx - 1; i >= 1; i--) {
        for (int j: cnt[i]) {
            cout << "? " << ans.back() << ' ' << 2 << ' ';
            cout << ans.back() << ' ' << j << endl;
            int t;
            cin >> t;
            if (t != 1) {
                ans.push_back(j);
                continue;
            }
        }
    }

    cout << "! " << ans.size() << ' ';
    for (int x: ans) {
        cout << x << ' ';
    }
    cout << endl;
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
