#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> DIRS = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
constexpr int MOD = int(1e9 + 7);

class Solution {
public:
    // 使用邻接表存储数
    vector<vector<int>> g;

    // p1 存储的是d1对应的路径
    /**
    d1 往下走的最长路径
    d2 往下走的次长路径（如果d1[i] == d2[i], 表示i点有两条最长的路径)
    up 网上走的路径
    **/
    vector<int> d1, d2, p1, up;

    void dfs1(int u, int father) {
        /**
        计算d1, d2, p1
        **/
        d1[u] = d2[u] = 0;
        for (int j : g[u]) {
            // 遍历所有的子节点
            // 需要跳过父节点，避免反向遍历
            if (j == father) continue;
            dfs1(j, u);
            // 子路径加1（此处的边权是1）
            int d = d1[j] + 1;
            if (d >= d1[u]) {
                // 先将当前最长路径给次长路径
                d2[u] = d1[u];
                // 更新最长路径
                d1[u] = d;
                p1[u] = j;
            } else if (d >= d2[u]) {
                // 只比次大值大，更新次大值
                d2[u] = d;
            }
        }
    }

    void dfs2(int u, int father) {
        for (int j : g[u]) {
            if (j == father) continue;
            if (j == p1[u]) {
                // j在u往下走的最长路径上, 比较父节点的up和往下走的次大值
                up[j] = max(up[u], d2[u]) + 1;
            } else {
                up[j] = max(up[u], d1[u]) + 1;
            }
            dfs2(j, u);
        }
    }

    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges) {
        // 初始化g, 修改为指定大小
        g.resize(n);
        d1 = d2 = p1 = up = vector<int>(n);

        // 存储图
        for (auto &e : edges) {
            int a = e[0], b = e[1];
            g[a].push_back(b);
            g[b].push_back(a);
        }
        vector<int> res;
        dfs1(0, -1);
        dfs2(0, -1);

        int min_heigh = n + 1;
        for (int i = 0; i < n; ++i) {
            // 遍历所有节点，找到最小的高度
            min_heigh = min(min_heigh, max(d1[i], up[i]));
        }
        for (int i = 0; i < n; ++i) {
            // 再次遍历所有节点，如果该点高度等于最小高度则加入答案， 这一步也可以合并到上一步中，为了清晰则不单独写。
            if (max(d1[i], up[i]) == min_heigh) res.push_back(i);
        }

        return res;
    }
};