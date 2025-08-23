#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
#define For(i, n) for (int(i) = 0; i < (n); i++)

// const int N = 5e5 + 5;
// vector<int> g[N];
// int pa[N], de[N];

// void solve2() {
//     int n;
//     cin >> n;
//     For(i, n + 1) g[i].clear(), pa[i] = 0, de[i] = 0;

//     For(i, n - 1) {
//         int u, v;
//         cin >> u >> v;
//         g[u].push_back(v);
//         g[v].push_back(u);
//         de[u]++;
//         de[v]++;
//     }

//     vector<int> lst = {1};
//     int ans = 0, tot = 1;

//     for (int dep = 1; dep <= n; dep++) {
//         vector<int> nxt;
//         for (auto u: lst) {
//             for (auto v: g[u]) {
//                 if (v == pa[u])
//                     continue;
//                 pa[v] = u;
//                 nxt.push_back(v);
//                 tot++;
//             }

//             while (u != 1 && de[u] - 1 == 0) {
//                 de[pa[u]]--;
//                 de[u]--;
//                 tot--;
//                 u = pa[u];
//             }
//         }
//         ans = max(ans, tot);
//         lst = nxt;
//     }

//     cout << n - ans << "\n";
// }

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1, vector<int>());
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<vector<int>> pa(n + 1, vector<int>(20, -1));
    vector<int> depth(n + 1);
    vector<int> dfn(n + 1);
    int timer = 0;


    auto dfs = [&](this auto &&dfs, int i, int fa, int d) -> void {
        depth[i] = d;
        dfn[i] = ++timer;
        for (int v: g[i]) {
            if (v != fa) {
                pa[v][0] = i;
                dfs(v, i, d + 1);
            }
        }
    };
    dfs(1, -1, 0);

    for (int i = 1; i < 20; i++) {
        for (int j = 1; j <= n; j++) {
            int p = pa[j][i - 1];
            if (p != -1) {
                pa[j][i] = pa[p][i - 1];
            }
        }
    }

    auto get_lca = [&](int x, int y) -> int {
        for (int i = 19; i >= 0; i--) {
            int p1 = pa[x][i], p2 = pa[y][i];
            if (p1 != p2 && p1 != -1 && p2 != -1) {
                x = p1, y = p2;
            }
        }
        return pa[x][0];
    };

    map<int, vector<int>> mp;
    for (int i = 2; i <= n; i++) {
        mp[depth[i]].push_back(i);
    }
    for (auto &[d, vec]: mp) {
        sort(vec.begin(), vec.end(), [&](int a, int b) { return dfn[a] < dfn[b]; });
    }

    int ans = 0;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        int sum = 1;
        for (int x: it->second) {
            sum += depth[x];
        }

        for (int j = 0; j < it->second.size() - 1; j++) {
            sum -= depth[get_lca(it->second[j], it->second[j + 1])];
        }
        ans = max(ans, sum);
    }

    cout << n - ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}
