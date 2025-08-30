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
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    int n, m, l;
    cin >> n >> m >> l;

    vector<pair<char, int>> v1(m), v2(l);
    For(i, m) {
        char s;
        int t;
        cin >> s >> t;
        v1[i] = {s, t};
    }
    For(i, l) {
        char s;
        int t;
        cin >> s >> t;
        v2[i] = {s, t};
    }

    auto mv = [&](char ch) -> pii {
        if (ch == 'U')
            return {-1, 0};
        if (ch == 'D')
            return {1, 0};
        if (ch == 'L')
            return {0, -1};
        return {0, 1};
    };

    int dr = r2 - r1, dc = c2 - c1;
    int i = 0, j = 0;
    int ans = 0;
    auto check = [&](int a, int b) -> bool {
        if (b == 0)
            return false;
        return a % b == 0;
    };

    while (i < m && j < l) {
        auto [sr, sc] = mv(v1[i].first);
        auto [tr, tc] = mv(v2[j].first);
        int ddr = tr - sr;
        int ddc = tc - sc;
        int len = min(v1[i].second, v2[j].second);

        if (ddr == 0 && ddc == 0) {
            if (dr == 0 && dc == 0)
                ans += len;
        } else if (ddr == 0) {
            if (dr == 0 && check(-dc, ddc)) {
                int t = (-dc) / ddc;
                if (t >= 1 && t <= len)
                    ans += 1;
            }
        } else if (ddc == 0) {
            if (dc == 0 && check(-dr, ddr)) {
                int t = (-dr) / ddr;
                if (t >= 1 && t <= len)
                    ans += 1;
            }
        } else {
            if (ddr * dc == ddc * dr && check(-dr, ddr) && check(-dc, ddc)) {
                int t1 = (-dr) / ddr;
                int t2 = (-dc) / ddc;
                if (t1 == t2 && t1 >= 1 && t1 <= len)
                    ans += 1;
            }
        }

        dr += ddr * len;
        dc += ddc * len;
        v1[i].second -= len;
        v2[j].second -= len;
        if (v1[i].second == 0)
            i++;
        if (v2[j].second == 0)
            j++;
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
