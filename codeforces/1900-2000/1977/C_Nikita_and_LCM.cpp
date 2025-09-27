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
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int mx = *max_element(a.begin(), a.end());

    int L = 1;
    for (int i = 0; i < n; i++) {
        L = lcm(L, a[i]);
        if (L > mx) {
            cout << n << "\n";
            return;
        }
    }

    set<int> in(a.begin(), a.end());
    int ans = 0;
    for (int d = 1; d * d <= L; d++) {
        if (L % d == 0) {
            for (int x: {d, L / d}) {
                if (in.count(x))
                    continue;
                int cur = 1;
                int cnt = 0;
                for (auto v: a) {
                    if (x % v == 0) {
                        cnt++;
                        cur = lcm(cur, v);
                    }
                }
                if (cur == x)
                    ans = max(ans, cnt);
            }
        }
    }

    cout << ans << "\n";
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
