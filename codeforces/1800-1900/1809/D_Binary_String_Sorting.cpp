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

constexpr int C1 = int(1e12);
constexpr int C2 = int(1e12) + 1;

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    int ans = inf;
    vector<int> pre(n + 1), suf(n + 1);

    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i];
        if (s[i] == '1') {
            pre[i + 1]++;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1];
        if (s[i] == '0') {
            suf[i]++;
        }
    }

    for (int i = 0; i <= n; i++) {
        int cost = 0;
        if (i + 1 < n && s[i] == '1' && s[i + 1] == '0') {
            cost = C1 + pre[i] * C2 + suf[i + 2] * C2;
        } else {
            cost = pre[i] * C2 + suf[i] * C2;
        }
        ans = min(ans, cost);
    }

    if (ans == inf) {
        ans = 0;
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
