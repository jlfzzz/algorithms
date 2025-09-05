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
    int n, s, x;
    cin >> n >> s >> x;
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];

    vector<int> pre_max(n + 1), pre_x(n + 1);
    pre_max[0] = 0;

    for (int i = 1; i <= n; i++) {
        pre_max[i] = pre_max[i - 1];
        pre_x[i] = pre_x[i - 1];
        if (a[i] > x) {
            pre_max[i] = i;
        }

        if (a[i] == x) {
            pre_x[i] = i;
        }
    }

    map<int, vector<int>> mp;
    mp[0].push_back(0);
    int pre = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        pre += a[i];
        if (mp.contains(pre - s)) {
            auto &st = mp[pre - s];
            int pre_mx = pre_max[i], last_x = pre_x[i];

            if (last_x > pre_mx) {
                auto it1 = ranges::lower_bound(st, pre_mx);
                auto it2 = ranges::lower_bound(st, last_x);
                ans += it2 - it1;
            }
        }
        mp[pre].push_back(i);
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
