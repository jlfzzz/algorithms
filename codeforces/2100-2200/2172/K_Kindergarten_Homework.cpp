#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
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
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
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

#ifdef LOCAL
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    int n, m, q;
    rd(n, m, q);

    vector<string> g(n);
    for (int i = 0; i < n; ++i) {
        rd(g[i]);
    }

    vector<int> qs(q);
    for (int i = 0; i < q; ++i) {
        rd(qs[i]);
    }

    const int MAXV = 1'000'000;
    vector<ll> cnt(MAXV + 1, 0);
    auto processLine = [&](const string &s) {
        int L = (int) s.size();
        for (int i = 0; i < L; ++i) {
            char c0 = s[i];
            if (c0 < '0' || c0 > '9')
                continue;

            ll sum = 0;
            ll prod = 1;
            ll cur = 0;
            bool lastDigit = false;

            for (int j = i; j < L; ++j) {
                char c = s[j];
                if (c >= '0' && c <= '9') {
                    int d = c - '0';
                    if (!lastDigit)
                        cur = d;
                    else
                        cur = cur * 10 + d;

                    if (cur > MAXV)
                        break;

                    ll val = sum + prod * cur;
                    if (val > MAXV)
                        break;

                    int len = j - i + 1;
                    if (len >= 2) {
                        cnt[val]++;
                    }
                    lastDigit = true;
                } else {
                    if (!lastDigit) {
                        break;
                    }
                    if (c == '+') {
                        prod *= cur;
                        if (prod > MAXV)
                            break;
                        sum += prod;
                        if (sum > MAXV)
                            break;
                        prod = 1;
                        cur = 0;
                    } else {
                        prod *= cur;
                        if (prod > MAXV)
                            break;
                        cur = 0;
                    }
                    lastDigit = false;
                }
            }
        }
    };

    for (int r = 0; r < n; ++r) {
        string s = g[r];
        processLine(s);
        reverse(s.begin(), s.end());
        processLine(s);
    }
    for (int c = 0; c < m; ++c) {
        string s;
        s.reserve(n);
        for (int r = 0; r < n; ++r)
            s.push_back(g[r][c]);
        processLine(s);
        reverse(s.begin(), s.end());
        processLine(s);
    }
    for (int c0 = 0; c0 < m; ++c0) {
        string s;
        int r = 0, c = c0;
        while (r < n && c < m) {
            s.push_back(g[r][c]);
            ++r;
            ++c;
        }
        if (!s.empty()) {
            processLine(s);
            reverse(s.begin(), s.end());
            processLine(s);
        }
    }
    for (int r0 = 1; r0 < n; ++r0) {
        string s;
        int r = r0, c = 0;
        while (r < n && c < m) {
            s.push_back(g[r][c]);
            ++r;
            ++c;
        }
        if (!s.empty()) {
            processLine(s);
            reverse(s.begin(), s.end());
            processLine(s);
        }
    }

    for (int c0 = 0; c0 < m; ++c0) {
        string s;
        int r = 0, c = c0;
        while (r < n && c >= 0) {
            s.push_back(g[r][c]);
            ++r;
            --c;
        }
        if (!s.empty()) {
            processLine(s);
            reverse(s.begin(), s.end());
            processLine(s);
        }
    }
    for (int r0 = 1; r0 < n; ++r0) {
        string s;
        int r = r0, c = m - 1;
        while (r < n && c >= 0) {
            s.push_back(g[r][c]);
            ++r;
            --c;
        }
        if (!s.empty()) {
            processLine(s);
            reverse(s.begin(), s.end());
            processLine(s);
        }
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            char ch = g[r][c];
            if (ch >= '0' && ch <= '9') {
                int val = ch - '0';
                if (val <= MAXV)
                    cnt[val]++;
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        int x = qs[i];
        ll res = 0;
        if (x >= 0 && x <= MAXV)
            res = cnt[x];
        prt(res);
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
