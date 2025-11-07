#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define all(x) (x).begin(), (x).end()
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
constexpr int MOD2 = int(998244353);
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

#ifdef LOCAL
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;
using namespace __gnu_pbds;

template<typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    ll n, m, q;
    rd(n, m, q);

    // 全局维护“最后一列”的顺序序列：按插入顺序递增的 key，value 为学生编号
    oset<pii> lastCol;
    long long nextKey = 0;
    for (ll i = 1; i <= n; i++) {
        long long id = (i - 1) * m + m;
        lastCol.insert({++nextKey, id});
    }

    // 每行：被移除的前 m-1 列列号（用于二分找第 y 个存在者）
    vector<oset<int>> removedCols(n + 1);
    // 每行：尾部序列（从最后一列移动进来的元素），同样用有序键维持顺序
    vector<oset<pii>> tails(n + 1);
    vector<long long> rowNextKey(n + 1, 0);

    auto kthPresentPos = [&](oset<int> &rem, int m1, int k) -> int {
        // 在区间 [1, m1] 中找第 k 个“未被移除”的位置
        int lo = 1, hi = m1, ans = m1;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            int removedLeq = (int) rem.order_of_key(mid + 1);
            int present = mid - removedLeq;
            if (present >= k) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    };

    while (q--) {
        int x, y;
        rd(x, y);

        long long removedId = -1;

        if ((int) m == 1) {
            // 只有最后一列，直接在 lastCol 上操作
            auto it = lastCol.find_by_order(x - 1);
            removedId = it->second;
            lastCol.erase(it);
            lastCol.insert({++nextKey, removedId});
            prt(removedId);
            continue;
        }

        if (y < (int) m) {
            // 在行 x 的前 m-1 列中或其尾部序列中取第 y 个
            int m1 = (int) m - 1;
            int cntFirst = m1 - (int) removedCols[x].size();
            if (y <= cntFirst) {
                int pos = kthPresentPos(removedCols[x], m1, y);
                removedId = (long long) (x - 1) * m + pos;
                removedCols[x].insert(pos);
            } else {
                int k = y - cntFirst - 1; // 0-based in tail
                auto itTail = tails[x].find_by_order(k);
                removedId = itTail->second;
                tails[x].erase(itTail);
            }

            // 把该行当前最后一列的人移入该行尾部序列
            auto itLast = lastCol.find_by_order(x - 1);
            long long toTail = itLast->second;
            lastCol.erase(itLast);
            tails[x].insert({++rowNextKey[x], toTail});

            // 离队者回到全局最后一列的队尾
            lastCol.insert({++nextKey, removedId});
        } else {
            // y == m：直接从全局最后一列取第 x 个
            auto it = lastCol.find_by_order(x - 1);
            removedId = it->second;
            lastCol.erase(it);
            lastCol.insert({++nextKey, removedId});
        }

        prt(removedId);
    }
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
