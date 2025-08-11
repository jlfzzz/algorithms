#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <vector>


// 为了提高 cin/cout 的效率
void setup_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

void solve() {
    int n;
    std::cin >> n;

    // adj: 存储有向图的邻接表
    // in_degree: 存储每个顶点的入度
    // 使用 n+1 的大小，方便进行1-based索引
    std::vector<std::vector<int>> adj(n + 1);
    std::vector<int> in_degree(n + 1, 0);

    // 读取邻接矩阵，构建有向图并计算入度
    for (int i = 0; i < n; ++i) {
        std::string row;
        std::cin >> row;
        for (int j = 0; j < n; ++j) {
            if (row[j] == '1') {
                // 顶点编号为 i+1 和 j+1
                // 建立从小编号到大编号的有向边
                int u = std::min(i + 1, j + 1);
                int v = std::max(i + 1, j + 1);
                adj[u].push_back(v);
                in_degree[v]++;
            }
        }
    }

    // 使用优先队列（最大堆）来保证每次都选择编号最大的节点
    std::priority_queue<int> q;

    // 将所有初始入度为0的节点加入优先队列
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    // 存储最终的排列结果
    std::vector<int> p;
    p.reserve(n);

    // 拓扑排序主循环
    while (!q.empty()) {
        // 取出当前可选节点中编号最大的一个
        int u = q.top();
        q.pop();

        p.push_back(u);

        // 遍历 u 的所有邻居 v
        for (int v: adj[u]) {
            // 将 v 的入度减1
            in_degree[v]--;
            // 如果 v 的入度变为0，则将其加入优先队列
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    // 输出结果
    for (int i = 0; i < n; ++i) {
        std::cout << p[i] << (i == n - 1 ? "" : " ");
    }
    std::cout << "\n";
}

int main() {
    setup_io();
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
