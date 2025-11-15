#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Flow = long long;
constexpr ll INF = 1e18;

struct Edge {
    int to, rev;
    Flow cap;
    ll cost;
};

struct MCMF {
    int n;
    vector<vector<Edge>> g;
    vector<ll> dis;
    vector<int> pre, pre_e;

    MCMF(int _n) : n(_n), g(_n), dis(_n), pre(_n), pre_e(_n) {}

    void addEdge(int u, int v, Flow cap, ll cost) {
        g[u].push_back({v, (int) g[v].size(), cap, cost});
        g[v].push_back({u, (int) g[u].size() - 1, 0, -cost});
    }

    bool spfa(int s, int t) {
        fill(dis.begin(), dis.end(), INF);
        vector<bool> inq(n, false);
        queue<int> q;

        dis[s] = 0;
        q.push(s);
        inq[s] = true;
        pre[s] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (int i = 0; i < g[u].size(); i++) {
                Edge &e = g[u][i];
                if (e.cap > 0 && dis[u] + e.cost < dis[e.to]) {
                    dis[e.to] = dis[u] + e.cost;
                    pre[e.to] = u;
                    pre_e[e.to] = i;
                    if (!inq[e.to]) {
                        q.push(e.to);
                        inq[e.to] = true;
                    }
                }
            }
        }
        return dis[t] != INF;
    }

    pair<Flow, ll> minCostMaxFlow(int s, int t) {
        Flow flow = 0;
        ll cost = 0;
        while (spfa(s, t)) {
            Flow f = INF;
            for (int v = t; v != s; v = pre[v]) {
                f = min(f, g[pre[v]][pre_e[v]].cap);
            }
            for (int v = t; v != s; v = pre[v]) {
                Edge &e = g[pre[v]][pre_e[v]];
                e.cap -= f;
                g[v][e.rev].cap += f;
                cost += (ll) f * e.cost;
            }
            flow += f;
        }
        return {flow, cost};
    }
};
