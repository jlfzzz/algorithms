#include <bits/stdc++.h>
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

template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    FenwickTree(int n) : tree(n + 1) {}

    void update(int i, T val) {
        for (; i < (int) tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }

    // 左闭右闭
    T rangeSum(int l, int r) const { return this->pre(r) - this->pre(l - 1); }

    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res += tree[i];
        }
        return res;
    }

    T getVal(int i) { return rangeSum(i, i); }

    void setVal(int i, T val) {
        T delta = val - getVal(i);
        update(i, delta);
    }

    // 点更新取 max
    void updateMax(int i, T val) {
        for (; i < (int) tree.size(); i += i & -i) {
            if (val > tree[i]) {
                tree[i] = val;
            }
        }
    }

    T preMax(int i) const {
        T res = numeric_limits<T>::min();
        for (; i > 0; i &= i - 1) {
            res = max(res, tree[i]);
        }
        return res;
    }
};

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

vl A;
struct Op {
    char type;
    int k;
    ll a;
    ll c;
    ll s;
};


void solve() {
    int n, m;
    rd(n, m);
    A.assign(n + 1, 0LL);

    vector<Op> ops;
    ops.reserve(m);
    vector<ll> vals;

    F(i, 1, m) {
        char op;
        rd(op);
        if (op == 'U') {
            int k;
            ll a;
            rd(k, a);
            ops.push_back(Op{op, k, a, 0, 0});
            if (a > 0)
                vals.pb(a);
        } else {
            ll c, s;
            rd(c, s);
            ops.push_back(Op{op, 0, 0, c, s});
        }
    }

    sort(all(vals));
    vals.erase(unique(all(vals)), vals.end());
    auto get_idx = [&](ll x) -> int { return (int) (lower_bound(all(vals), x) - vals.begin()) + 1; };

    FenwickTree<ll> bitCnt((int) vals.size());
    FenwickTree<ll> bitSumVal((int) vals.size());

    for (auto &o: ops) {
        if (o.type == 'U') {
            int k = o.k;
            ll a = o.a;
            ll old_val = A[k];

            if (old_val > 0) {
                int id = get_idx(old_val);
                bitCnt.update(id, -1);
                bitSumVal.update(id, -old_val);
            }
            if (a > 0) {
                int id = get_idx(a);
                bitCnt.update(id, +1);
                bitSumVal.update(id, +a);
            }

            A[k] = a;
        } else {
            ll c = o.c, s = o.s;
            if (s == 0) {
                prt("TAK");
                continue;
            }

            int le_cnt_idx = (int) (upper_bound(all(vals), s) - vals.begin());
            ll cnt_le = bitCnt.pre(le_cnt_idx);
            ll sum_le = bitSumVal.pre(le_cnt_idx);
            ll cnt_all = bitCnt.pre((int) vals.size());
            ll sum_all = bitSumVal.pre((int) vals.size());
            ll S = sum_all;
            ll cnt_gt = cnt_all - cnt_le;
            ll sum_gt = sum_all - sum_le;

            __int128 T = (__int128) S - ((__int128) sum_gt - (__int128) s * cnt_gt);
            __int128 need = (__int128) s * c;
            if (T >= need)
                prt("TAK");
            else
                prt("NIE");
        }
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
