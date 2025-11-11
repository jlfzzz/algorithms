#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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

#ifdef LOCAL
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

int INIT = [] { return 0; }();

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



class Solution {
public:
    long long minimumCost(vector<int> &nums, int k, int dist) {
        int n = nums.size();
        ll ans = LONG_LONG_MAX;

        multiset<ll> small, big;
        ll sum = 0;

        auto balance = [&]() {
            while (!big.empty() && small.size() < k - 1) {
                sum += *big.begin();
                small.insert(*big.begin());
                big.erase(big.begin());
            }
        };

        auto Add = [&](ll x) {
            balance();
            if (small.size() < k - 1) {
                small.insert(x);
                sum += x;
                return;
            }

            ll last = *small.rbegin();
            if (x < last) {
                small.erase(small.find(last));
                sum -= last;
                small.insert(x);
                sum += x;
                big.insert(last);
            } else {
                big.insert(x);
            }
        };

        auto Del = [&](ll x) {
            auto it1 = small.find(x);
            if (it1 == small.end()) {
                big.erase(big.find(x));
                return;
            }

            small.erase(it1);
            sum -= x;
            while (!small.empty() && !big.empty() && *big.begin() < *small.rbegin()) {
                ll t1 = *big.begin();
                ll t2 = *small.rbegin();
                sum -= t2 + t1;
                big.erase(big.find(t1));
                big.insert(t2);
                small.erase(small.find(t2));
                small.insert(t1);
            }
            balance();
        };

        int r = 1;
        for (int l = 1; l + k - 2 < n; l++) {
            while (r - l <= dist && r < n) {
                Add(nums[r]);
                r++;
            }
            ans = min(ans, sum);
            Del(nums[l]);
        }

        return ans + nums[0];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // Solution sol1;
    // ll n = 11;
    // vector<int> nums1{}, nums{};
}
