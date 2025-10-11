#include "bits/stdc++.h"
using namespace std;

using ll = long long;
using Flow = long long;

struct Edge {
    int to, rev;
    Flow cap;
    Flow original_cap;
};

// Dinic 最大流 + 最小割
struct Dinic {
    int n;
    vector<vector<Edge>> g;
    vector<int> level;
    vector<int> it;
    Dinic(int n = 0) { init(n + 5); }

    void init(int _n) {
        n = _n;
        g.assign(n, {});
        level.assign(n, -1);
        it.assign(n, 0);
    }

    void add(int u, int v, Flow c) {
        g[u].emplace_back(Edge{v, (int) g[v].size(), c, c}); // 保存原始容量
        g[v].emplace_back(Edge{u, (int) g[u].size() - 1, 0, 0});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const Edge &e: g[u]) {
                if (level[e.to] < 0 && e.cap > 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    Flow dfs(int u, int t, Flow f) {
        if (u == t)
            return f;
        for (int &i = it[u]; i < (int) g[u].size(); ++i) {
            Edge &e = g[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                Flow pushed = dfs(e.to, t, min(f, e.cap));
                if (pushed > 0) {
                    e.cap -= pushed;
                    g[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    Flow maxFlow(int s, int t) {
        Flow flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (true) {
                Flow pushed = dfs(s, t, numeric_limits<Flow>::max());
                if (pushed == 0)
                    break;
                flow += pushed;
            }
        }
        return flow;
    }

    vector<int> minCut(int s) {
        vector<int> vis(n);
        queue<int> q;
        q.push(s);
        vis[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &e: g[u]) {
                if (e.cap > 0 && !vis[e.to]) {
                    vis[e.to] = 1;
                    q.push(e.to);
                }
            }
        }
        return vis;
    }

    Flow minCutEdges(int s, int t) {
        vector<vector<Flow>> backup_cap(n);
        for (int i = 0; i < n; i++) {
            backup_cap[i].resize(g[i].size());
            for (int j = 0; j < g[i].size(); j++) {
                backup_cap[i][j] = g[i][j].cap;
            }
        }

        for (int i = 0; i < n; i++) {
            for (auto &e: g[i]) {
                if (e.original_cap > 0) {
                    e.cap = 1;
                } else {
                    e.cap = 0;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < g[i].size(); j++) {
                Edge &e = g[i][j];
                if (e.original_cap > 0) {
                    Edge &rev = g[e.to][e.rev];
                    rev.cap = 0;
                }
            }
        }

        Flow result = maxFlow(s, t);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < g[i].size(); j++) {
                g[i][j].cap = backup_cap[i][j];
            }
        }

        return result;
    }
};


namespace EK {
    struct Edge {
        int to, rev;
        Flow cap;
    };

    // EK算法 最大流
    struct EK {
        int n;
        vector<vector<Edge>> g;

        EK(int n = 0) { init(n + 5); }

        void init(int _n) {
            n = _n;
            g.assign(n, {});
        }

        void add(int u, int v, Flow c) {
            g[u].emplace_back(v, g[v].size(), c);
            g[v].emplace_back(u, g[u].size() - 1, 0);
        }

        Flow maxFlow(int s, int t) {
            Flow flow = 0;
            vector<int> pre(n), pre_e(n);

            auto bfs = [&]() -> bool {
                ranges::fill(pre, -1);
                queue<int> q;
                q.push(s);
                pre[s] = s;

                while (!q.empty() && pre[t] == -1) {
                    int u = q.front();
                    q.pop();
                    for (int i = 0; i < g[u].size(); i++) {
                        auto &e = g[u][i];
                        if (e.cap > 0 && pre[e.to] == -1) {
                            pre[e.to] = u;
                            pre_e[e.to] = i;
                            q.push(e.to);
                            if (e.to == t) {
                                return true;
                            }
                        }
                    }
                }

                return false;
            };

            while (bfs()) {
                Flow temp = LONG_LONG_MAX;
                for (int v = t; v != s; v = pre[v]) {
                    auto &e = g[pre[v]][pre_e[v]];
                    temp = min(temp, e.cap);
                }

                for (int v = t; v != s; v = pre[v]) {
                    auto &e = g[pre[v]][pre_e[v]];
                    e.cap -= temp;
                    g[v][e.rev].cap += temp;
                }

                flow += temp;
            }

            return flow;
        }
    };
} // namespace EK
