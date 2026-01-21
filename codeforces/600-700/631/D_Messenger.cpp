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

class KMP {
public:
    template<typename T>
    static vector<int> buildLPS(const T &s) {
        int n = s.size();
        vector<int> next(n, 0);
        int i = 1;
        int len = 0;
        while (i < n) {
            while (len > 0 && s[i] != s[len]) {
                len = next[len - 1];
            }
            if (s[i] == s[len]) {
                len++;
            }
            next[i] = len;
            i++;
        }
        return next;
    }

    template<typename T>
    static vector<int> search(const T &text, const T &pattern) {
        vector<int> result;
        int n = text.size();
        int m = pattern.size();

        if (m == 0) {
            result.resize(n);
            iota(all(result), 0);
            return result;
        }
        vector<int> lps = buildLPS(pattern);

        int i = 0; // text的索引
        int j = 0; // pattern的索引

        while (i < n) {
            while (j > 0 && text[i] != pattern[j]) {
                j = lps[j - 1];
            }
            if (text[i] == pattern[j]) {
                j++;
            }
            if (j == m) {
                result.push_back(i - m + 1);
                j = lps[j - 1];
            }
            i++;
        }

        return result;
    }
};

void solve() {
    int n, m;
    rd(n, m);

    vp stk1;
    F(i, 1, n) {
        string t;
        rd(t);
        int p = t.find('-');
        ll len = stoll(t.substr(0, p));
        char c = t[p + 1];

        if (!stk1.empty() && c == stk1.back().second) {
            stk1.back().first += len;
        } else {
            stk1.pb(len, c);
        }
    }

    vp stk2;
    F(i, 1, m) {
        string s;
        rd(s);
        int p = s.find('-');
        ll len = stoll(s.substr(0, p));
        char c = s[p + 1];

        if (!stk2.empty() && c == stk2.back().second) {
            stk2.back().first += len;
        } else {
            stk2.pb(len, c);
        }
    }

    ll ans = 0;
    if (SZ(stk2) == 1) {
        auto [len1, c1] = stk2[0];
        for (auto [len, c]: stk1) {
            if (c == c1 && len >= len1) {
                ans += len - len1 + 1;
            }
        }

        dbg(stk2, stk1);

        prt(ans);
        return;
    }

    vp c;
    F(i, 1, SZ(stk2) - 2) { c.pb(stk2[i]); }

    dbg(c);

    auto pos = KMP::search(stk1, c);

    dbg(pos);

    auto [len1, c1] = stk2[0];
    auto [len2, c2] = stk2.back();

    int len = max(SZ(stk2) - 2, 0);
    for (int p: pos) {
        if (p - 1 >= 0 && p + len < SZ(stk1) && stk1[p - 1].second == c1 && stk1[p - 1].first >= len1 &&
            stk1[p + len].second == c2 && stk1[p + len].first >= len2) {
            ans++;
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
