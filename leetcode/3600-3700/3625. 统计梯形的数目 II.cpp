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

class Solution {
public:
    int countTrapezoids(vector<vector<int>> &points) {
        int n = points.size();
        map<pii, map<int, int>> g1; // k and (b, cnt)  (k != inf)
        map<int, int> g2; // only for (k == inf)
        map<pii, map<pii, int>> g3; // mid point -> (k, cnt)

        for (int i = 0; i < n; i++) {
            int x1 = points[i][0];
            int y1 = points[i][1];
            for (int j = i + 1; j < n; j++) {
                int x2 = points[j][0];
                int y2 = points[j][1];

                int dx = x2 - x1;
                int dy = y2 - y1;

                pii mid = {x1 + x2, y1 + y2};

                if (dx == 0) {
                    g2[x1]++; // only x pos
                    g3[mid][{inf, inf}]++;
                } else if (dy == 0) {
                    g1[{0, 0}][y1]++; // only y pos
                    g3[mid][{0, 0}]++;
                } else {
                    if (dx < 0) {
                        dx = -dx;
                        dy = -dy;
                    }

                    int g = std::gcd(abs(dx), abs(dy));
                    dx /= g;
                    dy /= g;

                    // b = y - dy/dx * x = (y * dx - x * dy) / dx
                    int b = y1 * dx - x1 * dy;
                    g1[{dx, dy}][b]++;
                    g3[mid][{dx, dy}]++;
                }
            }
        }

        ll ans = 0;

        // part1
        for (auto &[p, v]: g1) {
            int suf = 0;
            for (auto &[b, c]: v) {
                suf += c;
            }

            for (auto &[b, c]: v) {
                suf -= c;
                ans += 1ll * c * suf;
            }
        }

        {
            int suf = 0;
            for (auto &[pos, c]: g2) {
                suf += c;
            }

            for (auto &[pos, c]: g2) {
                suf -= c;
                ans += c * suf;
            }
        }

        // part2
        for (auto &[mid, v]: g1) {
            int suf = 0;
            for (auto &[b, c]: v) {
                suf += c;
            }

            for (auto &[b, c]: v) {
                suf -= c;
                ans -= 1ll * c * suf;
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
