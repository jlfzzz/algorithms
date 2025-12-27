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

int Multitest = 1;

void init() {}

vector<int> manacher(const vector<int> &a) {
    const int SEP = 0;
    const int HEAD = -1;
    const int TAIL = -2;

    vector<int> t;
    t.reserve(a.size() * 2 + 3);

    t.push_back(HEAD);
    t.push_back(SEP);
    for (int x: a) {
        t.push_back(x);
        t.push_back(SEP);
    }
    t.push_back(TAIL);

    int n = t.size();
    vector<int> p(n, 0);
    int center = 0, R = 0;

    for (int i = 1; i < n - 1; i++) {
        if (i < R) {
            int mirror = 2 * center - i;
            p[i] = min(p[mirror], R - i);
        } else {
            p[i] = 1;
        }

        while (t[i + p[i]] == t[i - p[i]]) {
            p[i]++;
        }

        if (i + p[i] > R) {
            center = i;
            R = i + p[i];
        }
    }
    return p;
}

void solve() {
    int n;
    rd(n);

    vi a(n + 1);
    rv(a, 1);
    a[0] = -1;

    auto b = manacher(a);
    vl D2(n + 5, 0);

    int m = SZ(b);
    F(i, 4, m - 2) {
        int len = b[i] - 1;
        if (len <= 0)
            continue;

        if (i % 2 == 0) {
            int c = (i - 2) / 2;
            int k = (len + 1) / 2;

            D2[c - k + 1]++;
            D2[c + 1] -= 2;
            D2[c + k + 1]++;
        } else {
            int c = (i - 3) / 2;
            int k = len / 2;
            if (k == 0)
                continue;

            D2[c - k + 1]++;
            D2[c + 1]--;
            D2[c + 2]--;
            D2[c + k + 2]++;
        }
    }

    ll ans = 0;
    ll d = 0;
    ll val = 0;

    F(j, 0, n) {
        d += D2[j];
        val += d;

        if (j >= 1) {
            ll t = (val % MOD2) * (a[j] % MOD2) % MOD2;
            ans = (ans + t) % MOD2;
        }
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
    while (T--) {
        solve();
    }
}
