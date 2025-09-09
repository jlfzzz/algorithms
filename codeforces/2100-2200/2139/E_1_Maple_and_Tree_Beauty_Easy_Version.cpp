#include <bits/stdc++.h>
#include <vector>
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

    vector<vector<int>> g(n + 1, vector<int>());
    For(i, n - 1) {
        int p;
        cin >> p;
        g[p].push_back(i + 2);
    }

    vector<int> dep(n + 1, -1);
    queue<int> q;
    dep[1] = 0;
    q.push(1);
    vector<int> cnt(n + 1, 0);
    int mn = inf;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt[dep[u]] += 1;
        if (g[u].empty())
            mn = min(mn, dep[u]);
        for (int v: g[u]) {
            dep[v] = dep[u] + 1;
            q.push(v);
        }
    }

    vector<int> a;
    for (int d = 0; d <= mn; d++) {
        a.push_back(cnt[d]);
    }

    vector<int> dp(k + 1, 0);
    int ans = 0;
    dp[0] = 1;
    int pref = 0;
    for (int x: a) {
        pref += x;
        for (int i = k; i >= x; i--) {
            dp[i] |= dp[i - x];
        }
        int lo = max(0ll, pref - (n - k));
        int hi = min(k, pref);
        bool f = false;
        for (int i = lo; i <= hi; i++) {
            if (dp[i]) {
                f = true;
                break;
            }
        }
        if (f)
            ans += 1;
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
