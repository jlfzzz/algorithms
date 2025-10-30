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

int Multitest = 0;

void init() {}

void solve() {
    int n;
    rd(n);
    vi a(n + 1), b(n + 1);
    rv(a, 1);
    rv(b, 1);

    struct SegTree {
        int n;
        vi mn;
        vi id;
        void init(int _n) {
            n = _n;
            mn.assign(4 * (n + 1), inf);
            id.assign(4 * (n + 1), -1);
        }
        void pull(int p) {
            if (mn[p << 1] <= mn[p << 1 | 1]) {
                mn[p] = mn[p << 1];
                id[p] = id[p << 1];
            } else {
                mn[p] = mn[p << 1 | 1];
                id[p] = id[p << 1 | 1];
            }
        }
        void upd(int p, int l, int r, int idx, int val, int who) {
            if (l == r) {
                if (val < mn[p]) {
                    mn[p] = val;
                    id[p] = who;
                }
                return;
            }
            int m = (l + r) >> 1;
            if (idx <= m)
                upd(p << 1, l, m, idx, val, who);
            else
                upd(p << 1 | 1, m + 1, r, idx, val, who);
            pull(p);
        }
        void upd(int idx, int val, int who) { upd(1, 0, n, idx, val, who); }
        pii rangeMin(int p, int l, int r, int L, int R) {
            if (L > R || r < L || l > R)
                return {inf, -1};
            if (L <= l && r <= R)
                return {mn[p], id[p]};
            int m = (l + r) >> 1;
            auto a = rangeMin(p << 1, l, m, L, R);
            auto b = rangeMin(p << 1 | 1, m + 1, r, L, R);
            return (a.first <= b.first) ? a : b;
        }
        pii rangeMin(int L, int R) { return rangeMin(1, 0, n, L, R); }
    } st;

    vi dp(n + 1, inf), parent(n + 1, -1), chooseY(n + 1, -1);
    st.init(n);

    auto idx = [&](int i) { return max(0, i - a[i]); };

    dp[n] = 0;
    st.upd(idx(n), 0, n);

    bool f = false;
    for (int i = n; i >= 0; --i) {
        auto best = st.rangeMin(0, i);
        if (best.first >= inf)
            continue;

        if (i == 0) {
            int ans = best.first + 1;
            vi seq;
            for (int v = best.second; v != n; v = parent[v])
                seq.pb(chooseY[v]);
            reverse(all(seq));
            seq.pb(0);
            prt(ans);
            prv(seq);
            f = true;
            break;
        }

        int cur = best.second;
        int nxt = i + b[i];
        int cand = best.first + 1;
        if (cand < dp[nxt]) {
            dp[nxt] = cand;
            parent[nxt] = cur;
            chooseY[nxt] = i;
            st.upd(idx(nxt), cand, nxt);
        }
    }

    if (!f)
        prt(-1);
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
