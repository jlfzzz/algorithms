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
    int findMinimumTime(vector<vector<int>> &tasks) {
        sort(tasks.begin(), tasks.end(), [](const vector<int> &a, const vector<int> &b) { return a[1] < b[1]; });

        vector<vector<int>> st;
        st.push_back({-2, -2, 0});

        for (const auto &task: tasks) {
            int start = task[0];
            int end = task[1];
            int time = task[2];

            auto it = lower_bound(st.begin(), st.end(), start,
                                  [](const vector<int> &interval, int val) { return interval[1] < val; });

            int run = st.back()[2] - (*prev(it))[2];

            if (it != st.end() && (*it)[0] < start) {
                run -= (start - (*it)[0]);
            }

            int needed = time - run;

            if (needed > 0) {
                int cur = end;
                int t = needed;

                while (st.back()[1] >= cur - t + 1) {
                    auto top = st.back();
                    st.pop_back();
                    t += (top[1] - top[0] + 1);
                }

                int x = cur - t + 1;
                int y = st.back()[2] + t;

                st.push_back({x, cur, y});
            }
        }

        return st.back()[2];
    }
};

class Solution2 {
public:
    int findMinimumTime(vector<vector<int>> &tasks) {
        sort(tasks.begin(), tasks.end(), [](const vector<int> &a, const vector<int> &b) {
            if (a[1] != b[1])
                return a[1] < b[1];
            return a[0] > b[0];
        });

        set<int> S;

        for (auto &seg: tasks) {
            int L = seg[0];
            int R = seg[1];

            int cnt = 0;
            auto it = S.lower_bound(L);
            while (it != S.end() && *it <= R && cnt < seg[2]) {
                ++cnt;
                ++it;
            }

            if (cnt >= seg[2]) {
                continue;
            } else {
                int i = R;
                while (cnt < seg[2]) {
                    if (!S.contains(i)) {
                        S.insert(i);
                        cnt++;
                    }
                    i--;
                }
            }
        }

        return S.size();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // Solution sol1;
    // ll n = 11;
    // vector<int> nums1{}, nums{};
}
