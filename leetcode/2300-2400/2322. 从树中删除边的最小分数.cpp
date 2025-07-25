#include "bits/stdc++.h"
using namespace std;
using ll = long long;

class Solution {
    vector<int> A;
    vector<vector<int>> e;
    // sm：整棵树的异或和
    // sm2：连通块 B 的异或和
    int ans = 2e9, sm = 0, sm2;

    // 计算以 sn 为根，且不含 ban 的子树的异或和
    int dfs(int sn, int fa, int ban) {
        int ret = A[sn];
        for (int fn : e[sn])
            if (fn != fa && fn != ban)
                ret ^= dfs(fn, sn, ban);
        return ret;
    }

    // 在以 sn 为根，且不含 ban 的子树中枚举第二条被删除的边
    int dfs2(int sn, int fa, int ban) {
        int ret = A[sn];
        // 枚举连通块 D 的根 fn
        for (int fn : e[sn])
            if (fn != fa && fn != ban) {
                // 连通块 D 的异或和
                int x = dfs2(fn, sn, ban);
                ret ^= x;
                // 连通块 C 的异或和
                int y = sm2 ^ x;
                // 连通块 A 的异或和
                int z = sm ^ sm2;
                if (x > y) swap(x, y);
                if (x > z) swap(x, z);
                if (y > z) swap(y, z);
                ans = min(ans, z - x);
            }
        return ret;
    }

public:
    int minimumScore(vector<int> &nums, vector<vector<int>> &edges) {
        int n = nums.size();
        A = nums;
        e.resize(n, vector<int>());
        for (auto &edge : edges) e[edge[0]].push_back(edge[1]), e[edge[1]].push_back(edge[0]);

        // 计算整棵树的异或和
        for (int x : nums) sm ^= x;
        // 枚举树根以及第一条被删除的边
        for (int i = 0; i < n; i++)
            for (int j : e[i]) {
                // 计算连通块 B 的异或和，也就是计算以 i 为根，且不含 j 的子树的异或和
                sm2 = dfs(i, -1, j);
                // 枚举第二条被删除的边
                dfs2(i, -1, j);
            }

        return ans;
    }
};



class Solution {
public:
    int minimumScore(vector<int> &nums, vector<vector<int>> &edges) {
        int n = nums.size();
        vector<vector<int>> g(n, vector<int>());
        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<int> in(n);
        vector<int> out(n);
        int time = 0;
        vector<int> xors(n);

        auto dfs1 = [&](this auto &&dfs1, int i, int fa) -> int {
            int res = nums[i];
            in[i] = time++;
            for (int v : g[i]) {
                if (v == fa) {
                    continue;
                }

                res ^= dfs1(v, i);
            }
            xors[i] = res;
            out[i] = time;
            return res;
            };

        auto is_ancestor = [&](int x, int y) -> bool { return in[x] > in[y] and out[x] <= out[y]; };

        dfs1(0, -1);
        int ans = INT_MAX;
        int root = xors[0];
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int a, b, c;
                if (is_ancestor(i, j)) {
                    a = xors[i], b = xors[j] ^ xors[i], c = root ^ xors[j];
                } else if (is_ancestor(j, i)) {
                    a = xors[j], b = xors[i] ^ xors[j], c = root ^ xors[i];
                } else {
                    a = xors[i], b = xors[j], c = root ^ xors[i] ^ xors[j];
                }
                // if (ans == 6) {
                //     cout << i << endl << j << endl;
                // }
                ans = min(ans, max({ a, b, c }) - min({ a, b, c }));
            }
        }
        return ans;
    }
};
