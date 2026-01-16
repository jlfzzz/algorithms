#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const long long INF = 1e18;

// ==========================================
// solve1: Floyd 版本 (适合 N 较小，稠密图)
// 时间复杂度: O(N^3 + 3^K * N + 2^K * N^2)
// ==========================================
void solve1() {
    int n, k;
    cin >> n >> k;

    vector<vector<long long>> adj(n, vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj[i][j];
            if (i != j && adj[i][j] == 0)
                adj[i][j] = INF;
        }
    }

    vector<vector<long long>> dis = adj;

    for (int p = 0; p < n; ++p) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dis[i][p] != INF && dis[p][j] != INF) {
                    if (dis[i][p] + dis[p][j] < dis[i][j]) {
                        dis[i][j] = dis[i][p] + dis[p][j];
                    }
                }
            }
        }
    }

    int limit = 1 << k;
    vector<vector<long long>> dp(limit, vector<long long>(n, INF));

    for (int i = 0; i < k; ++i) {
        dp[1 << i][i] = 0;
    }

    for (int mask = 1; mask < limit; ++mask) {
        // (A) 子集枚举 (分裂合并)
        if ((mask & (mask - 1)) != 0) {
            for (int i = 0; i < n; ++i) {
                for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
                    if (dp[sub][i] != INF && dp[mask ^ sub][i] != INF) {
                        dp[mask][i] = min(dp[mask][i], dp[sub][i] + dp[mask ^ sub][i]);
                    }
                }
            }
        }

        // (B) 换根 (同层松弛) - 利用 Floyd 距离直接更新
        for (int i = 0; i < n; ++i) {
            if (dp[mask][i] == INF)
                continue;
            for (int j = 0; j < n; ++j) {
                if (dis[i][j] != INF) {
                    dp[mask][j] = min(dp[mask][j], dp[mask][i] + dis[i][j]);
                }
            }
        }
    }

    // 答案是连通了所有关键点 (mask = limit - 1)，根在任意位置的最小值
    long long ans = INF;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, dp[limit - 1][i]);
    }
}

// ==========================================
// solve2: Dijkstra 版本 (适合 N 较大，稀疏图)
// 时间复杂度: O(3^K * N + 2^K * M * logM)
// ==========================================
void solve2() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int limit = 1 << k;
    vector<vector<long long>> dp(limit, vector<long long>(n, INF));

    for (int i = 0; i < k; ++i) {
        dp[1 << i][i] = 0;
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    for (int mask = 1; mask < limit; ++mask) {
        // (A) 子集枚举 (分裂合并)
        if ((mask & (mask - 1)) != 0) {
            for (int i = 0; i < n; ++i) {
                for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
                    if (dp[sub][i] != INF && dp[mask ^ sub][i] != INF) {
                        dp[mask][i] = min(dp[mask][i], dp[sub][i] + dp[mask ^ sub][i]);
                    }
                }
            }
        }

        // (B) 换根 (同层松弛) - 使用 Dijkstra
        // 将当前 mask 下所有已知的代价作为源点推入队列
        for (int i = 0; i < n; ++i) {
            if (dp[mask][i] != INF) {
                pq.push({dp[mask][i], i});
            }
        }

        while (!pq.empty()) {
            pair<long long, int> top = pq.top();
            pq.pop();
            long long d = top.first;
            int u = top.second;

            if (d > dp[mask][u])
                continue;

            for (auto &edge: adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dp[mask][v] > dp[mask][u] + weight) {
                    dp[mask][v] = dp[mask][u] + weight;
                    pq.push({dp[mask][v], v});
                }
            }
        }
    }

    long long ans = INF;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, dp[limit - 1][i]);
    }
}

int main() {
    // 开启 IO 加速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 根据需要选择调用哪个 solve
    // 一般题目只会用一种，这里为了演示逻辑
    // solve1();
    solve2();

    return 0;
}
