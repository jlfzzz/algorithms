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
    vector<int> p(n + 1), q(n + 1);
    For(i, n) cin >> p[i + 1];
    For(i, n) cin >> q[i + 1];

    int L = n, R = -1;

    int ans = 0;

    map<int, int> pos1, pos2;
    for (int i = 1; i <= n; i++) {
        pos1[p[i]] = i;
        pos2[q[i]] = i;
    }

    auto calc = [&](int len) -> int { return len * (len + 1) / 2; };

    for (int mex = 1; mex <= n; mex++) {
        int p1 = pos1[mex];
        int p2 = pos2[mex];

        if (p2 < p1) {
            swap(p1, p2);
        }

        if (p1 != p2) {
            if (R == -1) {
                ans += calc(p2 - p1 - 1);
            } else if (L > p1 && R < p2) {
                ans += (L - p1) * (p2 - R);
            }
        }

        if (R == -1) {
            ans += calc(p1 - 1);
        } else if (R < p1 && L <= R) {
            ans += L * (p1 - R);
        }

        if (R == -1) {
            ans += calc(n - p2);
        } else if (L > p2) {
            ans += (L - p2) * (n - R + 1);
        }

        L = min(L, p1);
        R = max(R, p2);
    }

    cout << ans + 1 << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    while (T--)
        solve();
    return 0;
}
