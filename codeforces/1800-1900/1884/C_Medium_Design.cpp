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
    vector<pair<int, int>> evL, evR;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        if (l > 1) {
            evL.emplace_back(l, +1);
            evL.emplace_back(r + 1, -1);
        }
        if (r < m) {
            evR.emplace_back(l, +1);
            evR.emplace_back(r + 1, -1);
        }
    }
    auto calc = [](vector<pair<int, int>> &ev) -> int {
        if (ev.empty())
            return 0;
        sort(ev.begin(), ev.end());
        int cur = 0, ans = 0;
        for (int i = 0; i < ev.size();) {
            int x = ev[i].first;
            int t = 0;
            while (i < ev.size() && ev[i].first == x) {
                t += ev[i].second;
                i++;
            }
            cur += t;
            if (cur > ans)
                ans = cur;
        }
        return ans;
    };
    int ans = max(calc(evL), calc(evR));
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
