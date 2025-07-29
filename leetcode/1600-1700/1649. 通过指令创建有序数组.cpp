#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> DIRS = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
using ll = long long;
constexpr int MOD = int(1e9 + 7);

class FenwickTree {
private:
    vector<int> tree;

public:
    FenwickTree(int n) : tree(n + 1) {}

    void update(int index, int val = 1) {
        int i = index;
        for (; i < tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }

    int pre(int index) {
        int s = 0;
        while (index > 0) {
            s += tree[index];
            index -= index & -index;
        }
        return s;
    }
};


class Solution {
public:
    int createSortedArray(vector<int> &instructions) {
        int n = instructions.size();
        ll ans = 0;
        int mx = ranges::max(instructions);

        FenwickTree ft(mx);
        for (int x: instructions) {
            int less = ft.pre(x - 1);
            int greater = ft.pre(mx) - ft.pre(x);
            ans = (ans + min(less, greater)) % MOD;
            ft.update(x);
        }
        return ans;
    }
};
