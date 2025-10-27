#include <bits/stdc++.h>
using namespace std;

constexpr int N = int(1e5 + 5);

int INIT = [] { return 0; }();

using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);
using ll = long long;

struct Node {
    int mn, mx, lazy;
};

class Seg {
public:
    vector<Node> tree;
    Seg(int n) : tree(4 * n + 5) { build(1, 0, n - 1); }

    Node merge(Node &a, Node &b) { return {min(a.mn, b.mn), max(a.mx, b.mx), 0}; }

    void build(int o, int l, int r) {
        if (l == r) {
            tree[o] = {0, 0, 0};
            return;
        }

        int m = (l + r) / 2;
        build(o * 2, l, m);
        build(o * 2 + 1, m + 1, r);
        tree[o] = merge(tree[o * 2], tree[o * 2 + 1]);
    }

    void apply(Node &a, int lazy) {
        a.mn += lazy;
        a.mx += lazy;
        a.lazy += lazy;
    }

    void set(int o, int l, int r, int i, int val) {
        if (l == r) {
            tree[o] = {val, val, 0};
            // cout << "l = " << l << " i = " << i << " val = " << val << endl;
            return;
        }

        int m = (l + r) / 2;
        pushdown(o, l, r);
        if (i <= m) {
            set(o * 2, l, m, i, val);
        } else {
            set(o * 2 + 1, m + 1, r, i, val);
        }
        tree[o] = merge(tree[o * 2], tree[o * 2 + 1]);
    }

    void rangeAdd(int o, int l, int r, int ql, int qr, int delta) {
        if (l > qr || r < ql) {
            return;
        }

        if (l >= ql && r <= qr) {
            apply(tree[o], delta);
            return;
        }

        pushdown(o, l, r);
        int m = (l + r) / 2;
        rangeAdd(o * 2, l, m, ql, qr, delta);
        rangeAdd(o * 2 + 1, m + 1, r, ql, qr, delta);
        tree[o] = merge(tree[o * 2], tree[o * 2 + 1]);
    }

    void pushdown(int o, int l, int r) {
        int lazy = tree[o].lazy;
        if (l != r) {
            apply(tree[o * 2], lazy);
            apply(tree[o * 2 + 1], lazy);
        }
        tree[o].lazy = 0;
    }

    int findFirst(int o, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) {
            return -1;
        }

        if (tree[o].mn > 0 || tree[o].mx < 0) {
            return -1;
        }

        if (l == r) {
            if (tree[o].mx == 0 && tree[o].mn == 0) {
                return l;
            }
            return -1;
        }

        int m = (l + r) / 2;
        pushdown(o, l, r);
        int j = findFirst(o * 2, l, m, ql, qr);
        if (j == -1) {
            j = findFirst(o * 2 + 1, m + 1, r, ql, qr);
        }
        return j;
    }
};

class Solution {
public:
    int longestBalanced(vector<int> &nums) {
        int n = nums.size();

        Seg seg(n);
        unordered_map<int, int> last;
        vector<int> morvintale = nums;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            int delta = (x % 2 == 0) ? 1 : -1;
            if (last.contains(x)) {
                if (last[x] + 1 <= i - 1) {
                    seg.rangeAdd(1, 0, n - 1, last[x] + 1, i - 1, delta);
                }
            } else {
                if (i >= 1) {
                    seg.rangeAdd(1, 0, n - 1, 0, i - 1, delta);
                }
            }
            last[x] = i;
            seg.set(1, 0, n - 1, i, delta);
            int j = seg.findFirst(1, 0, n - 1, 0, i);
            if (j >= 0) {
                ans = max(ans, i - j + 1);
            }
        }

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution sol1;
    ll n = 11;
    vector<int> nums1{}, nums{};
}
