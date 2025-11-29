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

pll dp[2][2][3][10][17];
char vis[2][2][3][10][17];

class Solution {
public:
    long long totalWaviness(long long num1, long long num2) {
        auto calc = [&](ll x) {
            string s = to_string(x);
            int len = s.size();
            memset(vis, 0, sizeof(vis));
            auto dfs = [&](this auto &&dfs, int zero, int hi, int st, int pre, int i) -> pll {
                if (i == len) {
                    return {1, 0};
                }

                if (vis[zero][hi][st][pre][i]) {
                    return dp[zero][hi][st][pre][i];
                }

                pll res = {0, 0};
                int r = hi ? s[i] - '0' : 9;

                for (int l = 0; l <= r; l++) {
                    int nzero = zero && (l == 0);
                    int nhi = hi && (l == r);
                    int nst = 2;

                    if (!zero) {
                        if (l > pre) {
                            nst = 1;
                        } else if (l < pre) {
                            nst = 0;
                        } else {
                            nst = 2;
                        }
                    }

                    ll contrib = 0;
                    if (!zero && st != 2 && nst != 2) {
                        contrib = (nst ^ st);
                    }

                    pll sub = dfs(nzero, nhi, nst, l, i + 1);

                    res.first += sub.first;
                    res.second += sub.second + (contrib * sub.first);
                }

                vis[zero][hi][st][pre][i] = 1;
                return dp[zero][hi][st][pre][i] = res;
            };

            return dfs(1, 1, 2, 0, 0).second;
        };

        return calc(num2) - calc(num1 - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution sol1;
    ll n = 11;
    vector<int> nums1{}, nums{};
}
