#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int N = int(1e5 + 5);

namespace DEBUG {
    template<typename A, typename B>
    ostream &operator<<(ostream &os, const pair<A, B> &p) {
        return os << '(' << p.first << ", " << p.second << ')';
    }

    template<typename Tuple, size_t... Is>
    void print_tuple(ostream &os, const Tuple &t, index_sequence<Is...>) {
        ((os << (Is == 0 ? "" : ", ") << get<Is>(t)), ...);
    }

    template<typename... Args>
    ostream &operator<<(ostream &os, const tuple<Args...> &t) {
        os << '(';
        print_tuple(os, t, index_sequence_for<Args...>{});
        return os << ')';
    }

    template<typename T, typename = decltype(begin(declval<T>())), typename = enable_if_t<!is_same_v<T, string>>>
    ostream &operator<<(ostream &os, const T &v) {
        os << '{';
        bool first = true;
        for (auto &x: v) {
            if (!first)
                os << ", ";
            first = false;
            os << x;
        }
        return os << '}';
    }

    void debug_out() { cerr << endl; }

    template<typename Head, typename... Tail>
    void debug_out(Head H, Tail... T) {
        cerr << H;
        if (sizeof...(T))
            cerr << " ";
        debug_out(T...);
    }
} // namespace DEBUG

using namespace DEBUG;

#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)

int INIT = [] { return 0; }();

using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);
using ll = long long;

struct BIT {
    vector<int> tree;
    int n;
    BIT(int n) : tree(n + 10), n(n) {}
    void add(int i, int val) {
        for (; i <= n; i += i & -i) {
            tree[i] += val;
        }
    }
    int pre(int i) {
        int res = 0;
        while (i >= 1) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }
};

class Solution {
public:
    vector<int> popcountDepth(vector<long long> &nums, vector<vector<long long>> &queries) {
        int n = nums.size();
        vector<BIT> bits(10, n + 10);

        auto calc = [&](ll x) {
            int d = 0;
            while (x > 1) {
                x = __builtin_popcountll((unsigned long long) x);
                d++;
            }
            return d;
        };


        for (int j = 0; j < n; j++) {
            ll x = nums[j];
            int t = calc(x);
            bits[t].add(j + 1, 1);
        }

        vector<int> ans;
        for (auto &v: queries) {
            if (v[0] == 1) {
                int l = v[1];
                int r = v[2];
                int k = v[3];
                int res = bits[k].pre(r + 1) - bits[k].pre(l);
                ans.push_back(res);
            } else {
                ll idx = v[1];
                ll val = v[2];
                ll old = nums[idx];

                int t = calc(old);
                bits[t].add(idx + 1, -1);
                t = calc(val);
                bits[t].add(idx + 1, 1);
                nums[idx] = val;
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
}
