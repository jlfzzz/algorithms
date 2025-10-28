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
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f / 2;
constexpr int inf = 0x3f3f3f3f / 2;

namespace utils {
    void dbg() { cerr << "\n"; }

    template<typename T, typename... Args>
    void dbg(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        dbg(args...);
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

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

void solve() {
    int n, d;
    rd(n, d);
    vi days(n);
    rv(days);

    vi g(n + 1);
    g[0] = days[0] - 1;
    F(i, 1, n - 1) g[i] = days[i] - days[i - 1] - 1;
    g[n] = d - days.back();

    multiset<int> ms;
    F(i, 0, n - 1) ms.insert(g[i]);

    int ans = 0;
    F(i, 0, n - 1) {
        ms.erase(ms.find(g[i]));
        bool f1 = (i + 1 < n);
        int d1 = -1;
        if (f1) {
            ms.erase(ms.find(g[i + 1]));
            d1 = g[i] + g[i + 1] + 1;
            ms.insert(d1);
        }

        int mn = ms.empty() ? inf : *ms.begin();

        int tail = f1 ? max(0, g[n] - 1) : (g[n - 1] + g[n]);
        int cand2 = (mn == inf) ? tail : min(mn, tail);

        int cand1 = 0;
        if (!ms.empty()) {
            auto itL = prev(ms.end());
            int L = *itL;
            ms.erase(itL);
            int mn2 = ms.empty() ? inf : *ms.begin();
            int split = (L - 1) / 2;
            cand1 = (mn2 == inf) ? split : min(mn2, split);
            ms.insert(L);
        }

        ans = max(ans, max(cand1, cand2));

        if (f1) {
            ms.erase(ms.find(d1));
            ms.insert(g[i + 1]);
        }
        ms.insert(g[i]);
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
    while (T--)
        solve();
    return 0;
}
