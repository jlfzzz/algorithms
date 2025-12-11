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

template<typename T>
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

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    ll n, k;
    rd(n, k);

    vi a(n + 1);
    rv(a, 1);

    auto b = a;
    ranges::sort(b);
    b.erase(unique(all(b)), b.end());

    auto get = [&](int x) { return ranges::lower_bound(b, x) - b.begin() + 1; };

    int m = SZ(b) + 1;

    ll tot = 0;
    {
        BIT<int> t(m + 10);
        F(i, 1, n) {
            int id = get(a[i]);
            tot += t.rangeSum(id + 1, m);
            t.update(id, 1);
        }
    }

    ll least = tot - k;
    if (least <= 0) {
        prt(n * (n - 1) / 2);
        return;
    }

    vl cnt(n + 1);
    {
        BIT<int> t(m + 10);
        F(i, 1, n) {
            int id = get(a[i]);
            ll bigger = t.rangeSum(id + 1, m);
            cnt[i] += bigger;
            t.update(id, 1);
        }
    }
    {
        BIT<int> t(m + 10);
        D(i, n, 1) {
            int id = get(a[i]);
            ll smaller = t.rangeSum(1, id - 1);
            cnt[i] += smaller;
            t.update(id, 1);
        }
    }

    vl pref(n + 1);
    F(i, 1, n) { pref[i] = pref[i - 1] + cnt[i]; }

    BIT<int> bit(m + 10);
    ll inv = 0, ans = 0;
    int R = 1;

    F(L, 2, n - 1) {
        if (L > 2) {
            if (L - 1 <= R) {
                int id = get(a[L - 1]);
                ll ls = bit.pre(id - 1);
                inv -= ls;
                bit.update(id, -1);
            }
        }

        while (R + 1 <= n - 1) {
            ll sum = pref[R] - pref[L - 1];
            ll g = sum - inv;
            if (g >= least) {
                break;
            }
            R++;
            int id = get(a[R]);
            ll gt = bit.rangeSum(id + 1, m);
            inv += gt;
            bit.update(id, 1);
        }

        ll sum = pref[R] - pref[L - 1];
        ll g = sum - inv;
        if (g < least) {
            break;
        }

        ans += n - R;
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
