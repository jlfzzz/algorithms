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

    vp a(n);
    rv(a);

    map<pii, int> st;
    F(i, 0, n - 1) { st[a[i]] = i; }

    ll tot = 0;
    vl cnt(n);
    F(i, 0, n - 1) {
        auto [x1, y1] = a[i];
        F(j, i + 1, n - 1) {
            auto [x2, y2] = a[j];
            ll dx = x2 - x1, dy = y2 - y1;
            ll sx = x2 + x1, sy = y2 + y1;

            if ((sx - dy) % 2 || (sy + dx) % 2 || (sx + dy) % 2 || (sy - dx) % 2) {
                continue;
            }

            ll x3 = (sx - dy) / 2, y3 = (sy + dx) / 2;
            ll x4 = (sx + dy) / 2, y4 = (sy - dx) / 2;

            if (st.contains({x3, y3}) && st.contains({x4, y4})) {
                tot++;
                cnt[i]++;
                cnt[j]++;
                cnt[st[{x3, y3}]]++;
                cnt[st[{x4, y4}]]++;
            }
        }
    }

    ll ans = (tot - ranges::min(cnt)) / 2;

    prt(ans);
}

inline ull mask(ll x, ll y) { return ((ull) x << 31) + y; }

void solve2() {
    int n;
    rd(n);

    vp a(n);
    rv(a);

    unordered_map<ull, int> st;
    st.reserve(n * 2);
    st.max_load_factor(0.7f);
    F(i, 0, n - 1) { st[mask(a[i].fi, a[i].se)] = i; }

    ll tot = 0;
    vl cnt(n);
    F(i, 0, n - 1) {
        auto [x1, y1] = a[i];
        F(j, i + 1, n - 1) {
            auto [x2, y2] = a[j];
            ll dx = x2 - x1, dy = y2 - y1;
            ll sx = x2 + x1, sy = y2 + y1;

            if ((sx - dy) % 2 || (sy + dx) % 2 || (sx + dy) % 2 || (sy - dx) % 2) {
                continue;
            }

            ll x3 = (sx - dy) / 2, y3 = (sy + dx) / 2;
            ll x4 = (sx + dy) / 2, y4 = (sy - dx) / 2;

            ull k3 = mask(x3, y3);
            ull k4 = mask(x4, y4);

            if (st.contains(k3) && st.contains(k4)) {
                tot++;
                cnt[i]++;
                cnt[j]++;
                cnt[st[k3]]++;
                cnt[st[k4]]++;
            }
        }
    }

    ll ans = (tot - ranges::min(cnt)) / 2;

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
        solve2();
    }
}
