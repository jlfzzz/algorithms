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

int spf[N];
void sieve() {
    iota(spf, spf + N, 0);
    for (int i = 2; i * i < N; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < N; j += i)
                if (spf[j] == j)
                    spf[j] = i;
        }
    }
}

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

long long modInverse(long long a, long long m) {
    long long x, y;
    exgcd(a, m, x, y);
    return (x % m + m) % m;
}

int max_pow_val[N];
int rem_val[N];

void init() { sieve(); }

void solve() {
    int n;
    rd(n);
    vi p(n + 1), a(n + 1);
    F(i, 1, n) rd(p[i]);
    F(i, 1, n) rd(a[i]);

    vi cid(n + 1, -1), pos(n + 1, 0);
    vvi cycles;
    F(i, 1, n) {
        if (cid[i] == -1) {
            int cur = i;
            int id = SZ(cycles);
            vi cyc;
            while (cid[cur] == -1) {
                cid[cur] = id;
                pos[cur] = SZ(cyc);
                cyc.pb(cur);
                cur = p[cur];
            }
            cycles.pb(cyc);
        }
    }

    F(i, 1, n) {
        max_pow_val[i] = 1;
        rem_val[i] = 0;
    }

    vi ans(n + 1);
    vector<int> cyc_offset(SZ(cycles), -1);

    F(i, 1, n) {
        int id = cid[i];
        int len = SZ(cycles[id]);

        if (cyc_offset[id] != -1) {
            int shift = cyc_offset[id];
            int cur_pos = pos[i];
            int val_idx = cycles[id][(cur_pos + shift) % len];
            ans[i] = a[val_idx];
            continue;
        }

        long long step = 1;
        long long start = 0;

        int tmp = len;
        while (tmp > 1) {
            int pr = spf[tmp];
            int pe_L = 1;
            while (tmp % pr == 0) {
                tmp /= pr;
                pe_L *= pr;
            }
            int pe_G = max_pow_val[pr];
            int rem_G = rem_val[pr];

            int common_mod = min(pe_L, pe_G);
            int target_rem = rem_G % common_mod;

            long long diff = (target_rem - start) % common_mod;
            if (diff < 0)
                diff += common_mod;

            long long inv = modInverse(step, common_mod);
            long long k = (diff * inv) % common_mod;

            start = start + step * k;
            step = step * common_mod;
        }
        int best_val = inf;
        int best_x = -1;

        for (long long x = start; x < len; x += step) {
            int cur_pos = pos[i];
            int val_idx = cycles[id][(cur_pos + x) % len];
            int val = a[val_idx];
            if (val < best_val) {
                best_val = val;
                best_x = x;
            }
        }

        cyc_offset[id] = best_x;
        ans[i] = best_val;

        tmp = len;
        while (tmp > 1) {
            int pr = spf[tmp];
            int pe_L = 1;
            while (tmp % pr == 0) {
                tmp /= pr;
                pe_L *= pr;
            }
            if (pe_L > max_pow_val[pr]) {
                max_pow_val[pr] = pe_L;
                rem_val[pr] = best_x % pe_L;
            }
        }
    }

    // 输出
    F(i, 1, n) cout << ans[i] << (i == n ? "" : " ");
    cout << "\n";
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
