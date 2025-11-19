#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
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

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    int n, m;
    rd(n, m);

    vi a(n + 1);
    rv(a, 1);
    struct Modify {
        int p;
        int prev;
        int now;
    };

    struct Query {
        int l;
        int r;
        int t;
        int id;
    };

    vector<Modify> mods;
    vector<Query> qs;
    qs.reserve(m);
    mods.reserve(m);

    vi cur = a;

    F(i, 0, m - 1) {
        char op;
        rd(op);
        if (op == 'Q') {
            int l, r;
            rd(l, r);
            if (l > r) {
                swap(l, r);
            }
            Query qy{};
            qy.l = l;
            qy.r = r;
            qy.t = (int) mods.size();
            qy.id = (int) qs.size();
            qs.pb(qy);
        } else {
            int p, c;
            rd(p, c);
            Modify md{};
            md.p = p;
            md.prev = cur[p];
            md.now = c;
            mods.pb(md);
            cur[p] = c;
        }
    }

    int B = max(1, (int) pow(n, 2.0 / 3.0));

    ranges::sort(qs, [&](const Query &x, const Query &y) {
        int bx = x.l / B;
        int by = y.l / B;
        if (bx != by) {
            return bx < by;
        }
        int brx = x.r / B;
        int bry = y.r / B;
        if (brx != bry) {
            return brx < bry;
        }
        return x.t < y.t;
    });

    static int cnt[N];
    memset(cnt, 0, sizeof(cnt));
    int curL = 1, curR = 0, curT = 0;
    int diff = 0;

    auto add_pos = [&](int pos) {
        int color = a[pos];
        if (++cnt[color] == 1) {
            diff++;
        }
    };

    auto del_pos = [&](int pos) {
        int color = a[pos];
        if (--cnt[color] == 0) {
            diff--;
        }
    };

    auto apply_mod = [&](int idx) {
        const auto &md = mods[idx];
        int p = md.p;
        if (curL <= p && p <= curR) {
            del_pos(p);
            a[p] = md.now;
            add_pos(p);
        } else {
            a[p] = md.now;
        }
    };

    auto undo_mod = [&](int idx) {
        const auto &md = mods[idx];
        int p = md.p;
        if (curL <= p && p <= curR) {
            del_pos(p);
            a[p] = md.prev;
            add_pos(p);
        } else {
            a[p] = md.prev;
        }
    };

    vi ans(SZ(qs));

    for (const auto &q: qs) {
        while (curT < q.t) {
            apply_mod(curT);
            curT++;
        }
        while (curT > q.t) {
            curT--;
            undo_mod(curT);
        }
        while (curL > q.l) {
            curL--;
            add_pos(curL);
        }
        while (curR < q.r) {
            curR++;
            add_pos(curR);
        }
        while (curL < q.l) {
            del_pos(curL);
            curL++;
        }
        while (curR > q.r) {
            del_pos(curR);
            curR--;
        }
        ans[q.id] = diff;
    }

    F(i, 0, SZ(ans) - 1) { prt(ans[i]); }
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
