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


const int MAXN = 8e5 + 10;
const int SIGMA = 3;
struct Trie {
    int son[MAXN][SIGMA];
    int end[MAXN];
    int tot;

    Trie() { init(); }

    void init() {
        tot = 0;
        memset(son[0], 0, sizeof(son[0]));
        end[0] = 0;
    }

    int new_node() {
        ++tot;
        memset(son[tot], 0, sizeof(son[tot]));
        end[tot] = 0;
        return tot;
    }

    void insert(const string &s) {
        int p = 0;
        for (char c: s) {
            int u = c - 'a';
            if (!son[p][u])
                son[p][u] = new_node();
            p = son[p][u];
        }
        end[p]++;
    }

    int query(const string &s) {
        int p = 0;
        for (char c: s) {
            int u = c - 'a';
            if (!son[p][u])
                return 0;
            p = son[p][u];
        }
        return end[p];
    }
} trie;

int Multitest = 0;

void init() {}

mt19937 rng(random_device{}());

int rnd(long long x, long long y) { return uniform_int_distribution<int>(x, y)(rng); }

long long MOD = 1e18 + rnd(0, 1e9);
int BASE = 233 + rnd(0, 1e3);

struct HashSeq {
    int n;
    vector<__int128> P, H, HR;

    HashSeq(string s) {
        n = s.size();
        P.resize(n + 1);
        P[0] = 1;
        for (int i = 1; i <= n; i++)
            P[i] = P[i - 1] * BASE % MOD;

        H.resize(n + 1);
        H[0] = 0;
        for (int i = 1; i <= n; i++)
            H[i] = (H[i - 1] * BASE + (s[i - 1] ^ 7)) % MOD;

        HR.resize(n + 1);
        HR[0] = 0;
        for (int i = 1; i <= n; i++) {
            HR[i] = (HR[i - 1] * BASE + (s[n - i] ^ 7)) % MOD;
        }
    }

    long long query(int l, int r) const {
        if (l > r)
            return 0;
        __int128 res = (H[r] - (H[l - 1] * P[r - l + 1]) % (__int128) MOD);
        long long ans = (long long) ((res + (__int128) MOD) % (__int128) MOD);
        return ans;
    }

    long long query_rev_on_reversed(int l, int r) const {
        if (l > r)
            return 0;
        __int128 res = (HR[r] - (HR[l - 1] * P[r - l + 1]) % (__int128) MOD);
        return (long long) ((res + (__int128) MOD) % (__int128) MOD);
    }

    // auto is_pal = [&](int l, int r) { return hs.query(l, r) == hs.query_rev_sub(l, r); };
    long long query_rev_sub(int l, int r) const {
        if (l > r)
            return 0;
        int L = n - r + 1;
        int R = n - l + 1;
        __int128 res = (HR[R] - (HR[L - 1] * P[R - L + 1]) % (__int128) MOD);
        return (long long) ((res + (__int128) MOD) % (__int128) MOD);
    }

    // 滚动哈希，修改第idx位, 1-index
    // old_c -> new_c
    long long get_mod_hash(int idx, char old_c, char new_c) const {
        if (old_c == new_c)
            return (long long) H[n];

        __int128 power = P[n - idx];

        __int128 old_val = old_c ^ 7;
        __int128 new_val = new_c ^ 7;
        __int128 current_h = H[n];

        __int128 res = (current_h - (old_val * power) % (__int128) MOD + (new_val * power) % (__int128) MOD);

        return (long long) ((res % (__int128) MOD + (__int128) MOD) % (__int128) MOD);
    }
};

void solve() {
    int n, m;
    rd(n, m);

    set<ll> st;

    F(i, 1, n) {
        string s;
        rd(s);
        HashSeq hs(s);
        st.insert(hs.query(1, s.size()));
    }

    F(_, 1, m) {
        string s;
        rd(s);

        HashSeq hs(s);
        bool found = false;
        int len = s.size();

        for (int i = 0; i < len; i++) {
            if (found)
                break;

            char old = s[i];

            for (char c: {'a', 'b', 'c'}) {
                if (old == c)
                    continue;

                ll t = hs.get_mod_hash(i + 1, old, c);

                if (st.count(t)) {
                    found = true;
                    break;
                }
            }
        }

        prt(found ? "YES" : "NO");
    }
}

void solve2() {
    int n, m;
    rd(n, m);

    F(i, 1, n) {
        string s;
        rd(s);

        trie.insert(s);
    }

    F(_, 1, m) {
        string s;
        rd(s);

        int sz = SZ(s);
        bool found = false;
        auto dfs = [&](this auto &&dfs, int i, int diff, int u) -> void {
            if (found) {
                return;
            }

            if (i == sz) {
                if (diff == 1 && trie.end[u]) {
                    found = true;
                }
                return;
            }

            int cur = s[i] - 'a';
            F(j, 0, 2) {
                if (trie.son[u][j]) {
                    if (diff == 0) {
                        dfs(i + 1, (j != cur), trie.son[u][j]);
                    } else if (j == cur) {
                        dfs(i + 1, 1, trie.son[u][j]);
                    }
                }
            }
        };

        dfs(0, 0, 0);

        prt(found ? "YES" : "NO");
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
