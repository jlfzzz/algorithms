#include <bits/stdc++.h>
using namespace std;

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

int INIT = [] { return 0; }();

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);
using ll = long long;

#ifdef LOCAL
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif


class Solution {
public:
    long long maximumProfit(vector<ll> &prices, int k) {
        int n = prices.size();
        vector<vector<ll>> dp(k + 1, vector<ll>(3, -1e15));
        for (int i = 0; i <= k; i++) {
            dp[i][0] = 0;
        }

        for (int i = 1; i <= n; i++) {
            ll cur = prices[i - 1];
            for (int j = k; j >= 0; j--) {
                dp[j][1] = max(dp[j][1], dp[j][0] - cur);
                dp[j][2] = max(dp[j][2], dp[j][0] + cur);
                if (j >= 1) {
                    dp[j][0] = max({dp[j][0], dp[j - 1][1] + cur, dp[j - 1][2] - cur});
                }
            }
        }

        ll ans = -1e15;
        for (int i = 1; i <= k; i++) {
            ans = max(ans, dp[i][0]);
        }
        return ans;
    }

    long long maximumScore(vector<int> &nums, int k) {
        int n = nums.size();
        int mx_i = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] > nums[mx_i]) {
                mx_i = i;
            }
        }

        vector<ll> v1(nums.begin() + mx_i, nums.end());
        v1.insert(v1.end(), nums.begin(), nums.begin() + mx_i);

        vector<ll> v2(nums.begin() + mx_i + 1, nums.end());
        v2.insert(v2.end(), nums.begin(), nums.begin() + mx_i + 1);

        return max(maximumProfit(v1, k), maximumProfit(v2, k));
    }
};






int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // Solution sol1;
    // ll n = 11;
    // vector<int> nums1{}, nums{};
}
