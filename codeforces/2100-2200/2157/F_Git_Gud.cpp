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


void init() {}

constexpr int MAXN = 250000;
constexpr int M = 63;
constexpr int D = 5;

int Multitest = 0;

int ceildiv(int x, int y) { return x / y + (x % y != 0); }

vector<pair<int, int>> res[D][M];
vector<pair<int, int>> ans;

void dfs(int l, int r, int d) {
    if (l == r)
        return;
    if (l + 1 == r) {
        res[d][0].pb(l, 1);
        return;
    }

    int len = r - l;
    int b = ceildiv(len, M);
    vector<int> nds;

    for (int i = l; i < r;) {
        int j = min(i + b - 1, r);
        nds.pb(j);
        i = j + 1;
    }
    if (nds.back() != r)
        nds.pb(r);

    int lst = l;
    for (int i = 0; i < (int) nds.size(); i++) {
        dfs(lst, nds[i], d + 1);
        lst = nds[i] + 1;
    }

    if (nds.size() > 1) {
        for (int i = 0; i + 1 < (int) nds.size(); i++) {
            int y = nds[i];
            int lseg = nds[i + 1] - nds[i];
            res[d][i].pb(y, lseg);
        }
    }
}

void solve() {
    int n;
    rd(n);
    int N = MAXN;

    dfs(1, N, 1);

    for (int d = D - 1; d >= 1; d--) {
        for (int i = 0; i < M; i++) {
            auto &vec = res[d][i];
            sort(vec.begin(), vec.end());
            while (!vec.empty()) {
                ans.pb(vec.back());
                vec.pop_back();
            }
        }
    }

    cout << (int) ans.size() << '\n';
    for (auto [y, l]: ans) {
        cout << y << ' ' << l << '\n';
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
