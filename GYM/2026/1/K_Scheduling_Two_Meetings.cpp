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

int Multitest = 0;

void init() {}

void solve() {
    int n, m;
    rd(n, m);

    int u = 1 << m;
    vp dp1(u, {-1, inf}), dp2(u, {-1, inf});

    auto upd = [&](int mask, int idx, int cnt) -> void {
        if (idx == dp1[mask].se || idx == dp2[mask].se) {
            return;
        }

        if (cnt > dp1[mask].fi || (cnt == dp1[mask].fi && idx < dp1[mask].se)) {
            dp2[mask] = dp1[mask];
            dp1[mask] = {cnt, idx};
        } else if (cnt > dp2[mask].fi || (cnt == dp2[mask].fi && idx < dp2[mask].se)) {
            dp2[mask] = {cnt, idx};
        }
    };

    vi a(n);
    F(i, 1, n) {
        string s;
        rd(s);

        int mask = 0;
        F(j, 0, m - 1) {
            if (s[j] == 'Y') {
                mask |= 1 << j;
            }
        }

        a[i - 1] = mask;

        upd(mask, i, popcount((us) mask));
    }

    F(i, 0, m - 1) {
        F(mask, 0, u - 1) {
            if (mask >> i & 1) {
                upd(mask ^ (1 << i), dp1[mask].se, dp1[mask].fi);
                upd(mask ^ (1 << i), dp2[mask].se, dp2[mask].fi);
            }
        }
    }

    // -popcount, i, j
    tuple<int, int, int> ans{inf, inf, inf};

    F(i, 0, n - 1) {
        int mask = a[i];
        auto [cnt, j] = dp1[mask ^ (u - 1)];
        ll idx = i + 1;

        if (idx == j) {
            cnt = dp2[mask ^ (u - 1)].fi;
            j = dp2[mask ^ (u - 1)].se;
        }

        if (cnt == -1)
            continue;

        ll tot = popcount((us) mask) + cnt - m;

        ll u = min(idx, j);
        ll v = max(idx, j);
        // auto [u, v] = minmax<ll>(idx, j);

        tuple<int, int, int> cur = {-tot, u, v};

        if (cur < ans) {
            ans = cur;
        }
    }

    auto [c, i, j] = ans;
    if (c == inf) {
        prt("No");
        return;
    }

    prt(i, j);
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
