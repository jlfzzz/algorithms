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
    int n, m, l;
    cin >> n >> m >> l;

    vector<int> A(l);
    For(i, l) cin >> A[i];

    int s = 0;
    int mn = inf;
    bool f = false;
    for (int x: A) {
        s += x;
        if (x & 1) {
            f = true;
            mn = min(mn, x);
        }
    }

    vector<vector<int>> g(n + 1, vector<int>());
    For(i, m) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> d0(n + 1, inf), d1(n + 1, inf);
    queue<pair<int, int>> q;
    d0[1] = 0;
    q.emplace(1, 0);
    while (!q.empty()) {
        auto [u, p] = q.front();
        q.pop();
        if (p == 0) {
            for (int v: g[u]) {
                if (d1[v] == inf) {
                    d1[v] = d0[u] + 1;
                    q.emplace(v, 1);
                }
            }
        } else {
            for (int v: g[u]) {
                if (d0[v] == inf) {
                    d0[v] = d1[u] + 1;
                    q.emplace(v, 0);
                }
            }
        }
    }

    int maxEven = (s % 2 == 0 ? s : s - mn);
    int maxOdd = f ? (s % 2 == 1 ? s : s - mn) : -1;

    string ans(n, '0');
    for (int i = 1; i <= n; ++i) {
        bool ok = false;
        if (d0[i] != inf && maxEven >= d0[i])
            ok = true;
        if (!ok && f && d1[i] != inf && maxOdd >= d1[i])
            ok = true;
        ans[i - 1] = ok ? '1' : '0';
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
