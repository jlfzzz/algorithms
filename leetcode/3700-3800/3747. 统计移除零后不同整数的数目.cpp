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
    long long countDistinct(long long N) {
        string s = to_string(N);
        int n = s.size();
        ll ans = 0;
        ll pow9 = 1;
        for (int i = 0; i < n - 1; i++) {
            pow9 *= 9;
            ans += pow9;
        }

        vector<ll> pows(17, 1);
        for (int i = 1; i < 17; i++) {
            pows[i] = pows[i - 1] * 9;
        }

        for (int i = 0; i < n; i++) {
            int cur = s[i] - '0';
            ans += max((cur - 1), 0) * pows[n - i - 1];
        }
        // ans++;
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // Solution sol1;
    // ll n = 11;
    // vector<int> nums1{}, nums{};
}
