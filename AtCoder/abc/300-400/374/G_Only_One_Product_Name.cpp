#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
const ll N = 2005, M = 1919810, inf = 1e18, mod = 998442353;
vector<ll> e[N], g[N];
ll n;
char ca[N], cb[N];
bool vis[N];
ll dfn[N], low[N], t_cnt;
ll col[N], c_cnt;
ll st[N], top;
void tarjan(ll u) {
    dfn[u] = low[u] = ++t_cnt;
    vis[u] = 1, st[++top] = u;
    for (int v: e[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ll x;
        col[u] = ++c_cnt;
        do {
            x = st[top--];
            col[x] = c_cnt, vis[x] = 0;
        } while (x != u);
    }
}
ll dis[N][N];
ll p[N], vi[N];
bool dfs(ll u, ll tag) {
    if (vi[u] == tag)
        return 0;
    vi[u] = tag;
    for (int v: g[u]) {
        if (!p[v] || dfs(p[v], tag)) {
            p[v] = u;
            return 1;
        }
    }
    return 0;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> ca[i] >> cb[i];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (cb[i] == ca[j])
                e[i].pb(j);
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int u = 1; u <= n; ++u)
        for (int v: e[u])
            if (col[u] != col[v])
                dis[col[u]][col[v]] = 1;
    n = c_cnt;
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                dis[i][j] |= dis[i][k] & dis[k][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (dis[i][j])
                g[i].pb(j);
    ll ans = n;
    for (int i = 1; i <= n; ++i)
        ans -= dfs(i, i);
    cout << ans;
    return 0;
}
