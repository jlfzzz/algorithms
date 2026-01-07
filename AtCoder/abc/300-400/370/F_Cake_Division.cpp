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

void solve() {
    int n, k;
    rd(n, k);

    vi a(n);
    rv(a);

    vi b = a;
    b.ins(b.end(), all(a));

    ll tot = 0;
    for (int x: a)
        tot += x;

    vvi nxt(2 * n + 5, vi(20));

    auto check = [&](ll lim, int type) -> int {
        int r = 0;
        ll cur = 0;
        F(l, 0, 2 * n - 1) {
            if (r < l) {
                r = l;
                cur = 0;
            }
            while (r < 2 * n && cur < lim) {
                cur += b[r];
                r++;
            }
            if (cur >= lim)
                nxt[l][0] = r;
            else
                nxt[l][0] = 2 * n + 1;
            cur -= b[l];
        }

        nxt[2 * n][0] = 2 * n + 1;

        F(j, 0, 19) nxt[2 * n + 1][j] = 2 * n + 1;

        F(j, 1, 19) {
            F(i, 0, 2 * n) {
                if (nxt[i][j - 1] > 2 * n)
                    nxt[i][j] = 2 * n + 1;
                else
                    nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
            }
        }

        int cnt = 0;
        bool ok = 0;
        F(i, 0, n - 1) {
            int p = i;
            D(j, 19, 0) {
                if ((k >> j) & 1)
                    p = nxt[p][j];
            }
            if (p <= i + n) {
                ok = 1;
                if (type)
                    cnt++;
            }
        }
        if (type)
            return cnt;
        return ok;
    };

    ll lo = 1, hi = tot + 1;
    ll ans1 = 0;
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (check(mid, 0)) {
            ans1 = mid;
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    int valid = check(ans1, 1);
    prt(ans1, n - valid);
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
