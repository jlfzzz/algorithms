#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

const int MAXN = 200005;
const int M = 18;

vector<int> adj[MAXN];
int up[M][MAXN];
int dep[MAXN];
int n;

void dfs(int u, int p, int d) {
    dep[u] = d;
    up[0][u] = p;
    for (int v: adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
}

void build() {
    dfs(n, 0, 1);
    for (int i = 1; i < M; ++i) {
        for (int u = 1; u <= n; ++u) {
            if (up[i - 1][u] != 0) {
                up[i][u] = up[i - 1][up[i - 1][u]];
            }
        }
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }

    for (int i = M - 1; i >= 0; --i) {
        if (dep[u] - (1 << i) >= dep[v]) {
            u = up[i][u];
        }
    }

    if (u == v) {
        return u;
    }

    for (int i = M - 1; i >= 0; --i) {
        if (up[i][u] != 0 && up[i][u] != up[i][v]) {
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}

void solve() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    build();

    long long ans = 0;
    int cur = 1;

    for (int v = 1; v <= n; ++v) {
        if (v > 1) {
            cur = lca(cur, v);
        }
        ans += dep[cur];
    }

    cout << ans << endl;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
