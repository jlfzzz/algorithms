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

constexpr db EPS = 1e-9;

void solve() {
    db c, m, p, v;
    rd(c, m, p, v);

    auto dfs = [&](this auto &&dfs, int cnt, db a, db b, db pc) -> db {
        db res = pc;
        // if (cnt >= 30) {
        //     return res;
        // }

        if (a > EPS) {
            db take = min(a, v);
            if (b > EPS) {
                db na = a - take;
                db nb = b + take / 2;
                db npc = pc + take / 2;
                if (na < EPS)
                    na = 0;
                if (nb < EPS)
                    nb = 0;
                res += a * (1 + dfs(cnt + 1, na, nb, npc));
            } else {
                db na = a - take;
                db nb = 0;
                db npc = pc + take;
                if (na < EPS)
                    na = 0;
                res += a * (1 + dfs(cnt + 1, na, nb, npc));
            }
        }

        if (b > EPS) {
            db take = min(b, v);
            if (a > EPS) {
                db na = a + take / 2;
                db nb = b - take;
                db npc = pc + take / 2;
                if (nb < EPS)
                    nb = 0;
                if (na < EPS)
                    na = 0;
                res += b * (1 + dfs(cnt + 1, na, nb, npc));
            } else {
                db na = 0;
                db nb = b - take;
                db npc = pc + take;
                if (nb < EPS)
                    nb = 0;
                res += b * (1 + dfs(cnt + 1, na, nb, npc));
            }
        }
        return res;
    };

    auto ans = dfs(0, c, m, p);

    cout << fixed << setprecision(12) << ans << endl;
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
