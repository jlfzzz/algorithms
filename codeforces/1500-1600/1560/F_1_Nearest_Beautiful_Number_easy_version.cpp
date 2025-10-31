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
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;

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
    int n, k;
    rd(n, k);

    string s = to_string(n);
    s = "#" + s;
    int m = s.size();

    // dbg("s", s);

    vector memo(m, vector(2, vector<string>((1 << 10))));

    auto dfs = [&](this auto &&dfs, int i, int is_lo, int mask) -> string {
        int j = popcount((unsigned) mask);
        if (j > k) {
            return "?";
        }
        if (j == k && !is_lo) {
            F(k, 0, 9) {
                if (mask >> k & 1) {
                    return string(m - i, char('0' + k));
                }
            }
        }

        if (i == m) {
            return popcount((unsigned) mask) <= k ? string() : "?";
        }

        auto &x = memo[i][is_lo][mask];
        if (x != "") {
            return x;
        }

        if (i == 0) {
            auto ss = dfs(i + 1, true, mask);
            return x = ss;
        }

        int lo = 0;
        if (i != 0 && is_lo) {
            lo = s[i] - '0';
        }

        F(l, lo, 9) {
            if ((i == 0 && l == 0) || (i == 1 && l == 0)) {
                continue;
            }

            auto t = dfs(i + 1, is_lo && (l == (s[i] - '0')), mask | (1 << l));

            // dbg("t", t);
            if (t != "?") {
                t.insert(t.begin(), char('0' + l));
                return x = t;
            }
        }


        return x = "?";
    };

    auto ans = dfs(0, true, 0);

    ll tt = stoll(ans);
    prt(tt);
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
