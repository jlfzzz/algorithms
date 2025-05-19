#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>
#include <queue>
#include <cstring>
#include <array> 
#include <bitset>
#include <stack>
#include <set>
#include <random>

using namespace std;

class TreeAncestor {
public:
    vector<vector<int>> sons;
    vector<int> fa;
    vector<int> depth;
    // 爷爷，第1，2，4，8，16个爷爷爷爷爷爷...
    vector<vector<int>> pa;
    TreeAncestor(int n, vector<int> &parent) {
        int m = bit_width(static_cast<unsigned>(n));
        pa.resize(n, vector<int>(m, -1));
        for (int i = 0; i < n; i++) {
            pa[i][0] = parent[i];
        }
        for (int i = 0; i < m - 1; i++) {
            for (int x = 0; x < n; x++) {
                // 带初始化的if
                // 注意 p 被赋值为了 pa[x][i]
                if (int p = pa[x][i]; p != -1) {
                    // 注意右边的也是i
                    pa[x][i + 1] = pa[p][i];
                }
            }
        }

        sons.resize(n);
        depth.resize(n);
        fa.resize(n);
        depth[0] = 0;
        fa[0] = -1;
        for (int i = 1; i < n; i++) {
            int father = parent[i];
            sons[father].emplace_back(i);
            fa[i] = father;
        }

        queue<int> q;
        q.emplace(0);
        while (!q.empty()) {
            int curr_fa = q.front();
            q.pop();
            for (int child : sons[curr_fa]) {
                q.emplace(child);
                depth[child] = depth[fa[child]] + 1;
            }
        }
    }

    // int getKthAncestor(int node, int k) {
    //     if (depth[node] < k) {
    //         return -1;
    //     }
    //     while (k > 0) {
    //         node = fa[node];
    //         k--;
    //     }
    //     return node;
    // }
    int getKthAncestor(int node, int k) {
        int m = bit_width((unsigned)k); // k 的二进制长度
        for (int i = 0; i < m; i++) {
            if (k >> i & 1) { // k 的二进制从低到高第 i 位是 1
                node = pa[node][i];
                if (node < 0) break;
            }
        }
        return node;
    }

    // 另一种写法，不断去掉 k 的最低位的 1
    int getKthAncestor2(int node, int k) {
        for (; k && node != -1; k &= k - 1) {
            node = pa[node][countr_zero((unsigned)k)];
        }
        return node;
    }
};