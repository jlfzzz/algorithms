#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> g[N];
int n, m;

int dfn[N], low[N], timestamp;
bool inStack[N];
stack<int> st;
int scc_cnt;
vector<vector<int>> sccs;

void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    st.push(u);
    inStack[u] = true;

    for (int v: g[u]) {
        if (!dfn[v]) { // v 未访问
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            // v 在栈中，说明有回边
            low[u] = min(low[u], dfn[v]);
        }
    }

    // 找到一个 SCC
    if (dfn[u] == low[u]) {
        vector<int> comp;
        while (true) {
            int x = st.top();
            st.pop();
            inStack[x] = false;
            comp.push_back(x);
            if (x == u)
                break;
        }
        sccs.push_back(comp);
        scc_cnt++;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            tarjan(i);
    }

    cout << "SCC 数量: " << scc_cnt << "\n";
    for (auto &comp: sccs) {
        cout << "SCC: ";
        for (int x: comp)
            cout << x << " ";
        cout << "\n";
    }
}
