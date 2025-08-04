#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> colors(n + 1);
    For(i, n) { cin >> colors[i + 1]; }

    ll cost = 0;
    vector<vector<pll>> graph(n + 1);

    // 有根树结构
    vector<ll> parent(n + 1, 0);
    vector<ll> cost_to_parent(n + 1, 0);
    vector<map<ll, ll>> mem(n + 1); // mem[v][color] = v到该颜色子节点的总边权

    // 读取边并构建图
    For(i, n - 1) {
        ll x, y, c;
        cin >> x >> y >> c;
        graph[x].emplace_back(y, c);
        graph[y].emplace_back(x, c);
    }

    // DFS建立有根树（以1为根）
    function<void(int, int)> dfs = [&](int v, int par) {
        parent[v] = par;
        for (auto [u, c]: graph[v]) {
            if (u != par) {
                cost_to_parent[u] = c;
                mem[v][colors[u]] += c;
                dfs(u, v);
            }
        }
    };

    dfs(1, 0);

    // 计算初始答案
    for (int v = 2; v <= n; v++) {
        if (colors[v] != colors[parent[v]]) {
            cost += cost_to_parent[v];
        }
    }

    // 处理查询
    for (int i = 0; i < q; i++) {
        ll v, new_color;
        cin >> v >> new_color;

        ll old_color = colors[v];

        if (old_color != new_color) {
            // 1. 处理到子节点的边
            cost += mem[v][old_color]; // 原来同色(免费)现在异色(收费)
            cost -= mem[v][new_color]; // 原来异色(收费)现在同色(免费)

            // 2. 处理到父节点的边
            if (v != 1) { // 不是根节点
                ll par = parent[v];
                ll edge_cost = cost_to_parent[v];

                // 更新答案
                if (old_color != colors[par])
                    cost -= edge_cost; // 移除旧贡献
                if (new_color != colors[par])
                    cost += edge_cost; // 添加新贡献

                // 更新父节点的mem
                mem[par][old_color] -= edge_cost;
                if (mem[par][old_color] == 0) {
                    mem[par].erase(old_color);
                }
                mem[par][new_color] += edge_cost;
            }

            colors[v] = new_color;
        }

        cout << cost << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
