#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fori(n) for (int i = 0; i < (n); ++i)
#define ford(n) for (int i = (n); i >= 0; --i)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> nums(n);
    fori(n) {
        int l;
        cin >> l;
        vector<int> t(l);
        for (int j = 0; j < l; j++) {
            cin >> t[j];
        }
        nums[i] = std::move(t);
    }

    vector<vector<int>> graph;
    vector<pii> edges;
    int mx_vertex = 0;
    ll max_initial_mex = 0;

    // 构建图的边
    fori(n) {
        auto &v = nums[i];
        unordered_set<int> st;
        for (int x: v) {
            st.insert(x);
        }
        int u = 0; // 当前MEX
        while (st.contains(u)) {
            ++u;
        }
        max_initial_mex = max(max_initial_mex, (ll) u);

        int next_v = u + 1; // 添加u后的新MEX
        while (st.contains(next_v)) {
            ++next_v;
        }

        mx_vertex = max(mx_vertex, next_v);
        edges.emplace_back(u, next_v);
    }

    // 构建邻接表
    graph.resize(mx_vertex + 1);
    vector<int> outdegree(mx_vertex + 1, 0);
    for (auto &[u, v]: edges) {
        graph[u].push_back(v);
        outdegree[u]++;
    }

    // DP计算f[i] - 从i开始能到达的最大顶点
    vector<ll> f(mx_vertex + 1);
    ll global_max = max_initial_mex; // 全局下界

    // 从大到小DP
    for (int u = mx_vertex; u >= 0; --u) {
        f[u] = u;
        for (int v: graph[u]) {
            f[u] = max(f[u], f[v]);
        }
        // 如果出度>=2，可以删除其他边只保留最优的
        if (outdegree[u] >= 2) {
            global_max = max(global_max, f[u]);
        }
    }

    ll ans = 0;

    // 计算答案
    for (int i = 0; i <= min(mx_vertex, m); ++i) {
        ans += max(global_max, f[i]);
    }

    // 如果m > mx_vertex，剩余部分直接累加
    if (m > mx_vertex) {
        ll start = mx_vertex + 1;
        ll end = m;
        ans += (start + end) * (end - start + 1) / 2;
    }

    cout << ans << '\n';
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
