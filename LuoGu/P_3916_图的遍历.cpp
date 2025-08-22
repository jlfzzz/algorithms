#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;
int n, m;
vector<int> g[N];

// Tarjan
int dfn[N], low[N], ts;
bool inStack[N];
stack<int> st;
int scc_id[N], scc_cnt;
vector<int> scc_nodes[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++ts;
    st.push(u);
    inStack[u] = true;
    for (int v: g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        ++scc_cnt;
        while (true) {
            int x = st.top();
            st.pop();
            inStack[x] = false;
            scc_id[x] = scc_cnt;
            scc_nodes[scc_cnt].push_back(x);
            if (x == u)
                break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);

    // 每个 SCC 的“本地最大点编号”
    vector<int> scc_max(scc_cnt + 1, 0);
    for (int i = 1; i <= scc_cnt; ++i)
        for (int x: scc_nodes[i])
            scc_max[i] = max(scc_max[i], x);

    // 建缩点 DAG（按原方向）
    vector<vector<int>> dag(scc_cnt + 1);
    vector<int> indeg(scc_cnt + 1, 0);
    for (int u = 1; u <= n; ++u) {
        for (int v: g[u]) {
            int a = scc_id[u], b = scc_id[v];
            if (a != b) {
                dag[a].push_back(b);
                ++indeg[b];
            }
        }
    }

    // 拓扑序
    queue<int> q;
    vector<int> topo;
    topo.reserve(scc_cnt);
    for (int i = 1; i <= scc_cnt; ++i)
        if (indeg[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        for (int v: dag[u]) {
            if (--indeg[v] == 0)
                q.push(v);
        }
    }

    // 逆拓扑 DP：dp[u] = max(本地最大, 所有后继 v 的 dp[v])
    vector<int> dp(scc_cnt + 1, 0);
    for (int i = scc_cnt - 1; i >= 0; --i) {
        int u = topo[i];
        int best = scc_max[u];
        for (int v: dag[u])
            best = max(best, dp[v]);
        dp[u] = best;
    }

    // 还原到每个原始点
    for (int i = 1; i <= n; ++i) {
        cout << dp[scc_id[i]] << (i == n ? '\n' : ' ');
    }
    return 0;
}
