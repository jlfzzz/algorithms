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
    int n, x;
    cin >> n >> x;
    vector<int> p(n + 1);
    For(i, n) cin >> p[i + 1];

    int pos = -1;
    for (int i = 1; i <= n; i++) {
        if (p[i] == x)
            pos = i;
    }

    int l = 1, r = n + 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (p[m] <= x)
            l = m;
        else
            r = m;
    }
    int final_pos = l;

    vector<pii> ans;
    if (pos != final_pos) {
        ans.emplace_back(pos, final_pos);
        swap(p[pos], p[final_pos]);

        l = 1, r = n + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (p[m] <= x)
                l = m;
            else
                r = m;
        }
        if (p[l] != x) {
            for (int i = 1; i <= n; i++) {
                if (p[i] == x)
                    pos = i;
            }
            if (pos != final_pos) {
                ans.emplace_back(pos, final_pos);
                swap(p[pos], p[final_pos]);
            }
        }
    }

    cout << ans.size() << '\n';
    for (auto &[i, j]: ans) {
        cout << i << ' ' << j << '\n';
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
