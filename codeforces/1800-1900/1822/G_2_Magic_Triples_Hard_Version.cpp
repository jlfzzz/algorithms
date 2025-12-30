#include <bits/stdc++.h>
using namespace std;
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
#define us unsigned
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
constexpr int MOD2 = int(1e9 + 7);
constexpr int MOD = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

namespace utils {
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

    template<typename T>
    void prt(const T &x) {
        cout << x << '\n';
    }

    template<typename T, typename... Args>
    void prt(const T &first, const Args &...rest) {
        cout << first;
        ((cout << ' ' << rest), ...);
        cout << '\n';
    }

    template<typename T>
    void prv(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prv(const vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            if (i > start_index)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void rd(T &x) {
        cin >> x;
    }

    template<typename T, typename... Args>
    void rd(T &x, Args &...args) {
        cin >> x;
        rd(args...);
    }

    template<typename A, typename B>
    void rd(pair<A, B> &p) {
        cin >> p.first >> p.second;
    }

    template<typename T>
    void rv(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rv(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }
} // namespace utils

#ifdef WOAIHUTAO
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);
    vl a(n);
    rv(a);

    // 1. 排序，为二分查找做准备
    sort(all(a));

    // 获取数组最大值，用于剪枝优化 (替代代码中的 1e9)
    ll mx_val = a.back();

    // 辅助函数：查找 val 在数组中出现的次数
    // 对应原代码中的 find 函数
    auto get_cnt = [&](ll val) -> ll {
        // 如果查找的值超过最大值，直接返回 0，防止无效查找
        if (val > mx_val)
            return 0;
        auto it1 = lower_bound(all(a), val);
        if (it1 == a.end() || *it1 != val)
            return 0;
        auto it2 = upper_bound(all(a), val);
        return (ll) (it2 - it1);
    };

    ll ans = 0;
    ll last_contribution = 0; // 用于处理连续相同数字的优化

    for (int i = 0; i < n; i++) {
        // 如果当前数字与前一个相同，直接复用上次计算的结果
        if (i > 0 && a[i] == a[i - 1]) {
            ans += last_contribution;
            continue;
        }

        ll cur_ans = 0;
        ll val = a[i]; // 当前作为中间项

        // 枚举因子 j (对应原代码中的 j)
        // j * j <= val 是只枚举到平方根
        // j * val <= mx_val 是关键剪枝：如果 j 作为公比导致 next 太大，就没必要继续了
        // 注意：原代码的逻辑里 j 既充当 divisor 也充当 multiplier (在不同分支)
        for (ll j = 1; j * j <= val && j * val <= mx_val; ++j) {
            if (val % j != 0)
                continue;

            // 情况 1: j 是公比 (multiplier)
            // 此时：prev = val / j, next = val * j
            {
                ll now = j;
                // 如果 now == 1，说明公比为 1，即三个数相同 (val, val, val)
                if (now == 1) {
                    ll cnt = get_cnt(val);
                    if (cnt >= 3) {
                        cur_ans += (cnt - 1) * (cnt - 2);
                    }
                } else {
                    // prev = val / now, next = val * now
                    // 我们需要找到 prev 的数量和 next 的数量
                    ll cnt_prev = get_cnt(val / now);
                    ll cnt_next = get_cnt(val * now);
                    cur_ans += cnt_prev * cnt_next;
                }
            }

            // 情况 2: val / j 是公比
            // 此时：prev = j, next = val * (val / j)
            // 只有当 j*j != val 时才处理，避免完全平方数重复计算
            if (j * j != val) {
                ll now = val / j;
                // 同样检查公比为 1 的情况 (理论上 val/j==1 意味着 j==val，被上面 j*j<=val 限制了，除非 val=1，但 val=1
                // 时 j=1 已处理)
                if (now == 1) {
                    ll cnt = get_cnt(val);
                    if (cnt >= 3) {
                        cur_ans += (cnt - 1) * (cnt - 2);
                    }
                } else {
                    // prev = val / now (即 j), next = val * now
                    // 检查 potential next 是否越界
                    ll next_val = val * now;
                    // 这里原代码没有显式检查 next_val <= mx_val，因为二分查找会处理找不到的情况
                    // 但为了防止 long long 溢出或无效计算，get_cnt 里加了判断

                    ll cnt_prev = get_cnt(j);
                    ll cnt_next = get_cnt(next_val);
                    cur_ans += cnt_prev * cnt_next;
                }
            }
        }

        ans += cur_ans;
        last_contribution = cur_ans;
    }

    prt(ans);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--) {
        solve();
    }
}
