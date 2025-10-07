#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 500005, mod = 1e9 + 7;
int n, a[N], s[N], ans;
vector<int> e[N];
map<int, int> mp;

void dfs(int u, int fa) {
    if (u == 1)
        s[u] = 1;
    else if (fa == 1)
        s[u] = e[fa].size();
    else
        s[u] = s[fa] * (e[fa].size() - 1) % mod;
    for (int v: e[u])
        if (v != fa)
            dfs(v, u);
}
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        ++mp[a[i] * s[i] % mod];
        ans = max(ans, mp[a[i] * s[i] % mod]);
    }
    cout << n - ans;
}
