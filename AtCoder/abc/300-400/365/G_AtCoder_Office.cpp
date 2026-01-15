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

constexpr int N = 2e5 + 5;

int Multitest = 0;

void init() {}

vi pos[N];
const int B = 500;
ll dp[B][N];
int ids[N];
ll sum[N];

void solve() {
    int n, m;
    rd(n, m);

    vp a(m + 1);
    rv(a, 1);

    F(i, 1, m) { pos[a[i].se].pb(i); }

    int tot = 0;
    F(i, 1, n) {
        if (SZ(pos[i]) < B) {
            continue;
        }

        ids[i] = tot;
        sum[0] = 0;
        bool inside = false;

        F(j, 1, m) {
            sum[j] = sum[j - 1];

            if (inside) {
                sum[j] += (a[j].fi - a[j - 1].fi);
            }

            if (a[j].se == i) {
                inside = !inside;
            }
        }

        F(j, 1, n) {
            ll overlap = 0;
            for (size_t k = 0; k < pos[j].size(); k += 2) {
                int idx_in = pos[j][k];
                int idx_out = pos[j][k + 1];

                overlap += sum[idx_out] - sum[idx_in];
            }
            dp[tot][j] = overlap;
        }

        tot++;
    }

    int q;
    rd(q);

    while (q--) {
        int x, y;
        rd(x, y);

        if (SZ(pos[x]) < SZ(pos[y])) {
            swap(x, y);
        }

        if (SZ(pos[x]) >= B) {
            prt(dp[ids[x]][y]);
            continue;
        }

        auto &v1 = pos[x];
        auto &v2 = pos[y];

        int p1 = 0;
        int p2 = 0;
        int sz1 = SZ(v1);
        int sz2 = SZ(v2);

        ll ans = 0;
        while (p1 < sz1 && p2 < sz2) {
            ll l1 = a[v1[p1]].fi;
            ll r1 = a[v1[p1 + 1]].fi;
            ll l2 = a[v2[p2]].fi;
            ll r2 = a[v2[p2 + 1]].fi;

            ll L = max(l1, l2);
            ll R = min(r1, r2);

            if (L < R) {
                ans += R - L;
            }

            if (r1 < r2) {
                p1 += 2;
            } else {
                p2 += 2;
            }
        }
        prt(ans);
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
