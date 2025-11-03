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
    int n1, n2, n3;
    rd(n1, n2, n3);
    vl a(n1), b(n2), c(n3);
    rv(a);
    rv(b);
    rv(c);

    ranges::sort(a);
    ranges::sort(b);
    ranges::sort(c);

    auto calc = [&](vl &a, vl &b, vl &c) {
        ll sum1 = accumulate(all(a), 0ll);
        ll sum2 = accumulate(all(b), 0ll);
        ll sum3 = accumulate(all(c), 0ll);

        ll mn1 = a[0];
        ll mn2 = b[0];
        ll mn3 = c[0];

        vl res;
        {
            ll t3 = mn3;
            t3 -= sum2 + sum1 - mn1;
            ll sum = mn1 - t3 - (sum3 - mn3);
            res.pb(sum);
        }
        {
            ll t2 = mn2;
            t2 -= sum3 + sum1 - mn1;
            ll sum = mn1 - t2 - (sum2 - mn2);
            res.pb(sum);
        }
        {
            ll t2 = mn2;
            ll t3 = mn3;
            t2 -= sum3 - mn3;
            t3 -= sum2 - mn2;
            t2 -= sum1 - mn1;
            ll sum = mn1 - t2 - t3;
            res.pb(sum);
        }
        return ranges::max(res);
    };

    vl temp;
    temp.pb(calc(a, b, c)), temp.pb(calc(a, c, b)), temp.pb(calc(b, a, c));
    temp.pb(calc(b, c, a)), temp.pb(calc(c, a, b)), temp.pb(calc(c, b, a));
    prt(ranges::max(temp));
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
