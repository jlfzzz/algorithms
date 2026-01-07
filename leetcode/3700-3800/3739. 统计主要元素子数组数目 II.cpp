#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multiset =
    tree<pair<long long, long long>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int N = int(5e5 + 5);
int INIT = [] { return 0; }();

using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

template<typename T = long long>
class BIT {
    vector<T> tree;

public:
    BIT(int n) : tree(n + 1) {}

    void update(int i, T val) {
        for (; i < (int) tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }

    // 左闭右闭
    T rangeSum(int l, int r) const { return this->pre(r) - this->pre(l - 1); }

    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res += tree[i];
        }
        return res;
    }

    T getVal(int i) { return rangeSum(i, i); }

    void setVal(int i, T val) {
        T delta = val - getVal(i);
        update(i, delta);
    }

    // 点更新取 max
    void updateMax(int i, T val) {
        for (; i < (int) tree.size(); i += i & -i) {
            if (val > tree[i]) {
                tree[i] = val;
            }
        }
    }

    T preMax(int i) const {
        T res = numeric_limits<T>::min();
        for (; i > 0; i &= i - 1) {
            res = max(res, tree[i]);
        }
        return res;
    }
};

class Solution {
public:
    long long countMajoritySubarrays(vector<int> &nums, int target) {
        int n = SZ(nums);
        int offset = n + 2;

        vector<BIT<ll>> bits(2, BIT<ll>(2 * n + 5));
        bits[1].update(0 + offset, 1);
        int pre = 0;
        ll ans = 0;
        F(i, 0, n - 1) {
            int x = nums[i] == target ? 1 : -1;
            pre += x;

            auto &bit1 = bits[i & 1];
            auto &bit2 = bits[(i & 1) ^ 1];
            bit1.update(pre + offset, 1);

            ans += bit2.pre(pre + offset);
            ans += bit1.pre(pre + offset - 1);
        }

        return ans;
    }
};
