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

int Multitest = 1;

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
    int n;
    rd(n);

    string s;
    rd(s);

    string t(n, '0');
    F(i, 0, n - 1) { t[i] = s[i] ^ 1; }

    HashSeq hs2(t), hs1(s);

    auto Get = [&](HashSeq &hs, int l, int r) { return hs.query(l + 1, r + 1); };

    vi ans(n);
    F(i, 0, n - 1) {
        int pre = (i > 0) ? ans[i - 1] : 0;
        int cur = 0;

        if (pre == 0) {
            if (s[i] == t[0]) {
                cur = 1;
            }
        } else {
            int l = i - pre;
            while (l <= i) {
                auto vs = Get(hs1, l, i);
                auto vt = Get(hs2, 0, (i - l));

                if (vs == vt) {
                    cur = i - l + 1;
                    break;
                }

                l++;
            }
        }

        ans[i] = cur;
    }

    prv(ans);
}

vector<int> z_func(string word) {
    int n = word.size();
    vector<int> z(n, 0);
    int left = 0;
    int right = 0;
    for (int i = 1; i < n; i++) {
        if (i <= right) {
            z[i] = min(right - i + 1, z[i - left]);
        }
        while (i + z[i] < n && word[i + z[i]] == word[z[i]]) {
            left = i;
            right = i + z[i];
            z[i] += 1;
        }
    }
    return z;
}

void solve2() {
    int n;
    rd(n);

    string s;
    rd(s);

    string t(n, '0');
    F(i, 0, n - 1) { t[i] = s[i] ^ 1; }

    string s2 = t + '#' + s;

    auto z = z_func(s2);

    dbg(SZ(z));

    vi ans(n);
    F(i, n + 1, 2 * n) {
        int len = z[i];
        int idx = i - (n + 1);

        dbg(i, len, idx, idx + len - 1);
        if (idx + len - 1 >= 0)
            ans[idx + len - 1] = max(ans[idx + len - 1], len);
    }

    D(i, n - 2, 0) { ans[i] = max(ans[i], ans[i + 1] - 1); }

    prv(ans);
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
