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

struct LB {
    using i64 = long long;
    const int BASE = 63;
    vector<i64> d, p;
    int cnt, flag;

    LB() {
        d.resize(BASE + 1);
        p.resize(BASE + 1);
        cnt = flag = 0;
    }

    void clear() {
        d.assign(BASE + 1, 0);
        p.assign(BASE + 1, 0);
        cnt = flag = 0;
    }

    bool insert(i64 val) {
        for (int i = BASE - 1; i >= 0; i--) {
            if (val & (1ll << i)) {
                if (!d[i]) {
                    d[i] = val;
                    return true;
                }
                val ^= d[i];
            }
        }
        flag = 1;
        return false;
    }

    bool check(i64 val) {
        for (int i = BASE - 1; i >= 0; i--) {
            if (val & (1ll << i)) {
                val ^= d[i];
            }
        }
        return val == 0;
    }

    i64 ask_max() {
        i64 res = 0;
        for (int i = BASE - 1; i >= 0; i--) {
            if ((res ^ d[i]) > res)
                res ^= d[i];
        }
        return res;
    }

    i64 ask_min() {
        for (int i = 0; i <= BASE - 1; i++) {
            if (d[i])
                return d[i];
        }
        return 0;
    }

    void rebuild() {
        p.assign(BASE + 1, 0);
        cnt = 0;
        auto temp_d = d;

        for (int i = BASE - 1; i >= 0; i--) {
            if (temp_d[i]) {
                for (int j = i - 1; j >= 0; j--) {
                    if (temp_d[i] & (1ll << j))
                        temp_d[i] ^= temp_d[j];
                }
            }
        }
        for (int i = 0; i <= BASE - 1; i++) {
            if (temp_d[i])
                p[cnt++] = temp_d[i];
        }
    }

    i64 ask_kth_min(i64 k) {
        i64 total_sums = (1LL << cnt);
        if (k <= 0 || k > total_sums)
            return -1;

        i64 k_loop = k - 1;

        i64 res = 0;
        for (int i = 0; i < cnt; i++) {
            if (k_loop & (1LL << i))
                res ^= p[i];
        }
        return res;
    }

    i64 ask_kth_max(i64 k) {
        i64 total_sums = (1LL << cnt);
        if (k <= 0 || k > total_sums)
            return -1;

        i64 k_loop = total_sums - k;

        i64 res = 0;
        for (int i = 0; i < cnt; i++) {
            if (k_loop & (1LL << i))
                res ^= p[i];
        }
        return res;
    }

    void Merge(const LB &b) {
        for (int i = BASE - 1; i >= 0; i--) {
            if (b.d[i]) {
                insert(b.d[i]);
            }
        }
        flag = flag | b.flag;
        cnt = 0;
    }

    int get_rank() {
        int rank = 0;
        for (int i = 0; i <= BASE - 1; i++) {
            if (d[i] != 0) {
                rank++;
            }
        }
        return rank;
    }
};

int Multitest = 0;

void init() {}

void solve() {
    int n;
    rd(n);

    vi pref;
    int cur = 0;
    F(i, 1, n) {
        int x;
        rd(x);
        cur ^= x;
        pref.push_back(cur);
    }

    if (cur == 0) {
        prt(-1);
        return;
    }

    LB lb;
    for (int val: pref) {
        lb.insert(val);
    }

    lb.rebuild();
    prt(lb.cnt);
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
