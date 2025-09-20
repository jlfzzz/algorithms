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
    int n, w;
    cin >> n >> w;

    vector<vector<int>> g(n + 1, vector<int>());
    vector<int> parent(n + 1);
    parent[1] = 0;
    For(i, n - 1) {
        int p;
        cin >> p;
        parent[i + 2] = p;
        g[p].push_back(i + 2);
    }

    vector<int> r(n + 1, 0);
    function<void(int)> dfs = [&](int u) {
        int mx = u;
        for (int v: g[u]) {
            dfs(v);
            mx = max(mx, (int) r[v]);
        }
        r[u] = mx;
    };
    dfs(1);

    vector<int> fa(n + 1), sz(n + 1, 1);
    iota(fa.begin(), fa.end(), 0);
    function<int(int)> find = [&](int x) {
        while (fa[x] != x) {
            fa[x] = fa[fa[x]];
            x = fa[x];
        }
        return x;
    };
    auto unite = [&](int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b])
            swap(a, b);
        fa[b] = a;
        sz[a] += sz[b];
        return true;
    };

    auto nxt = [&](int x) { return x == n ? 1 : x + 1; };
    auto prv = [&](int x) { return x == 1 ? n : x - 1; };

    int c = n;
    int S = 0;

    For(qi, n - 1) {
        int x, y;
        cin >> x >> y;

        int rx = find(x);
        int rp = find(parent[x]);
        int cnt = 0;

        if (find(prv(x)) == rp)
            cnt += 1;
        if (find(r[x]) == rx && find(nxt(r[x])) == rp)
            cnt += 1;
        unite(rx, rp);
        c -= cnt;


        S += y;
        int W = w - S;
        cout << (2 * S + c * W) << (qi + 1 == n - 1 ? '\n' : ' ');
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
