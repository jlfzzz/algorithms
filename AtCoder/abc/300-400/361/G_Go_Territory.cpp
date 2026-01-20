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

int Multitest = 0;

void init() {}

struct DSU {
    vector<int> p;
    vector<bool> is_ocean;
    DSU(int n) : p(n), is_ocean(n, false) { iota(all(p), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void merge(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            p[rootX] = rootY;
            is_ocean[rootY] = is_ocean[rootY] | is_ocean[rootX];
        }
    }
    void set_ocean(int x) { is_ocean[find(x)] = true; }
};

const int MAX_COORD = 200005;

void solve() {
    int n;
    rd(n);
    vector<vector<int>> col_stones(MAX_COORD + 1);

    for (int i = 0; i < n; ++i) {
        int x, y;
        rd(x, y);
        col_stones[x].pb(y);
    }

    struct Segment {
        int l, r;
        int id;
        ll len;
    };

    vector<vector<Segment>> cols(MAX_COORD + 1);
    int seg_counter = 0;

    for (int x = 0; x <= MAX_COORD; ++x) {
        col_stones[x].pb(-1);
        col_stones[x].pb(MAX_COORD);
        sort(all(col_stones[x]));

        for (size_t i = 0; i < col_stones[x].size() - 1; ++i) {
            int y1 = col_stones[x][i];
            int y2 = col_stones[x][i + 1];

            int l = y1 + 1;
            int r = y2 - 1;

            if (l <= r) {
                cols[x].push_back({l, r, seg_counter++, (ll) (r - l + 1)});
            }
        }
    }

    DSU dsu(seg_counter);

    for (int x = 0; x <= MAX_COORD; ++x) {
        for (auto &seg: cols[x]) {
            bool ocean = false;
            if (x == 0)
                ocean = true;
            if (x == MAX_COORD)
                ocean = true;
            if (seg.l == 0)
                ocean = true;
            if (seg.r == MAX_COORD - 1)
                ocean = true;

            if (ocean) {
                dsu.set_ocean(seg.id);
            }
        }
    }

    for (int x = 0; x < MAX_COORD; ++x) {
        auto &curr_col = cols[x];
        auto &next_col = cols[x + 1];

        size_t i = 0, j = 0;
        while (i < curr_col.size() && j < next_col.size()) {
            auto &s1 = curr_col[i];
            auto &s2 = next_col[j];

            if (max(s1.l, s2.l) <= min(s1.r, s2.r)) {
                dsu.merge(s1.id, s2.id);
            }

            if (s1.r < s2.r) {
                i++;
            } else {
                j++;
            }
        }
    }

    ll ans = 0;
    for (int x = 0; x <= MAX_COORD; ++x) {
        for (auto &seg: cols[x]) {
            if (!dsu.is_ocean[dsu.find(seg.id)]) {
                ans += seg.len;
            }
        }
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
