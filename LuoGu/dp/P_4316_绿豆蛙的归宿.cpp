#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<vector<pair<int, int>>> g(n + 1), rg(n + 1); // g: 正向，rg: 反向 (v -> u)
    for (int i = 0; i < m; ++i) {
        int u, v;
        int w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        rg[v].emplace_back(u, w); // 反向边：从 v 回到 u，权重相同
    }

    vector<int> outdeg(n + 1);
    for (int i = 1; i <= n; ++i)
        outdeg[i] = (int) g[i].size();
    vector<int> rem = outdeg; // 剩余未处理的出边计数
    vector<long double> E(n + 1, 0.0L); // E[u] : u 到终点的期望长度
    vector<long double> sum(n + 1, 0.0L); // 累加 (w + E[v]) 的和

    deque<int> dq;
    // 所有 outdeg == 0 的节点入队（理论上根据题目，只有终点 n）
    for (int i = 1; i <= n; ++i)
        if (rem[i] == 0)
            dq.push_back(i);

    while (!dq.empty()) {
        int v = dq.front();
        dq.pop_front();
        // 对 v 的所有前驱 u：
        for (auto &pr: rg[v]) {
            int u = pr.first;
            long double w = pr.second;
            sum[u] += w + E[v]; // 累加 u->v 这条边对 u 的贡献 (w + E[v])
            rem[u]--; // 一个后继 v 已经处理完
            if (rem[u] == 0) {
                // 所有出边的后继都处理完，可以确定 E[u]
                if (outdeg[u] > 0)
                    E[u] = sum[u] / (long double) outdeg[u];
                else
                    E[u] = 0; // 不应发生（题目保证能到达终点），但保险处理
                dq.push_back(u);
            }
        }
    }

    cout.setf(std::ios::fixed);
    cout << setprecision(2) << (double) E[1] << '\n';
    return 0;
}
