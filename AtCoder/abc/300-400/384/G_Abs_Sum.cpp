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

template<typename T = long long>
class BIT {
    vector<T> tree;

public:
    BIT(int n) : tree(n + 1) {}

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

int Multitest = 0;

void init() {}

void solve() {
    int n;
    rd(n);
    vl a(n + 1), b(n + 1);
    rv(a, 1);
    rv(b, 1);

    vl vals;
    vals.reserve(2 * n);
    F(i, 1, n) {
        vals.pb(a[i]);
        vals.pb(b[i]);
    }
    sort(all(vals));
    vals.erase(unique(all(vals)), vals.end());

    auto get_rk = [&](ll v) -> int { return lower_bound(all(vals), v) - vals.begin() + 1; };
    int m = SZ(vals);

    BIT<ll> bit_cnt_a(m), bit_sum_a(m);
    BIT<ll> bit_cnt_b(m), bit_sum_b(m);

    int k;
    rd(k);
    struct Query {
        int x, y, id;
    };
    vector<Query> qs(k);
    F(i, 0, k - 1) {
        rd(qs[i].x, qs[i].y);
        qs[i].id = i;
    }

    int blk_sz = max(1, (int) (n / sqrt(max(1, k))));
    sort(all(qs), [&](const Query &u, const Query &v) {
        int bu = u.x / blk_sz, bv = v.x / blk_sz;
        if (bu != bv)
            return bu < bv;
        return (bu & 1) ? u.y < v.y : u.y > v.y;
    });

    ll cur_ans = 0;
    int cx = 0, cy = 0; 

    auto modify_a = [&](int idx, int op) {
        ll val = a[idx];
        int rk = get_rk(val);

        ll cnt_le = bit_cnt_b.pre(rk);
        ll sum_le = bit_sum_b.pre(rk);
        ll cnt_all = cy;
        ll sum_all = bit_sum_b.pre(m);

        ll delta = (cnt_le * val - sum_le) + ((sum_all - sum_le) - (cnt_all - cnt_le) * val);

        cur_ans += delta * op;

        bit_cnt_a.update(rk, op);
        bit_sum_a.update(rk, val * op);
    };

    auto modify_b = [&](int idx, int op) {
        ll val = b[idx];
        int rk = get_rk(val);

        ll cnt_le = bit_cnt_a.pre(rk);
        ll sum_le = bit_sum_a.pre(rk);
        ll cnt_all = cx;
        ll sum_all = bit_sum_a.pre(m);

        ll delta = (cnt_le * val - sum_le) + ((sum_all - sum_le) - (cnt_all - cnt_le) * val);

        cur_ans += delta * op;

        bit_cnt_b.update(rk, op);
        bit_sum_b.update(rk, val * op);
    };

    vl ans(k);
    for (const auto &q: qs) {
        while (cx < q.x)
            modify_a(++cx, 1);
        while (cx > q.x)
            modify_a(cx--, -1);
        while (cy < q.y)
            modify_b(++cy, 1);
        while (cy > q.y)
            modify_b(cy--, -1);
        ans[q.id] = cur_ans;
    }

    for (auto x: ans)
        prt(x);
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
