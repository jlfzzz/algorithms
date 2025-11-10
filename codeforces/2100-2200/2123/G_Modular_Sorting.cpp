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

int Multitest = 1;

void init() {}

ll calc(ll r_prev, ll r_curr, ll g) { return (r_curr - r_prev + g) % g; }

void solve() {
    int n;
    ll m;
    int q;
    rd(n, m, q);
    vl a(n + 1);
    rv(a, 1);

    vl divisors;
    for (ll i = 1; i * i <= m; ++i) {
        if (m % i == 0) {
            divisors.pb(i);
            if (i * i != m) {
                divisors.pb(m / i);
            }
        }
    }

    map<ll, ll> S;
    for (ll g: divisors) {
        ll bn = a[1] % g;
        F(i, 2, n) { bn += calc(a[i - 1] % g, a[i] % g, g); }
        S[g] = bn;
    }

    F(_, 1, q) {
        int type;
        rd(type);
        if (type == 1) {
            int i;
            ll x;
            rd(i, x);

            for (ll g: divisors) {
                ll old_ri = a[i] % g;
                ll new_ri = x % g;

                if (i == 1) {
                    S[g] -= old_ri;
                    S[g] += new_ri;
                    if (n > 1) {
                        ll r_plus_1 = a[i + 1] % g;
                        S[g] -= calc(old_ri, r_plus_1, g);
                        S[g] += calc(new_ri, r_plus_1, g);
                    }
                } else if (i == n) {
                    ll r_minus_1 = a[i - 1] % g;
                    S[g] -= calc(r_minus_1, old_ri, g);
                    S[g] += calc(r_minus_1, new_ri, g);
                } else {
                    ll r_minus_1 = a[i - 1] % g;
                    ll r_plus_1 = a[i + 1] % g;
                    S[g] -= calc(r_minus_1, old_ri, g);
                    S[g] -= calc(old_ri, r_plus_1, g);
                    S[g] += calc(r_minus_1, new_ri, g);
                    S[g] += calc(new_ri, r_plus_1, g);
                }
            }
            a[i] = x;

        } else {
            ll k;
            rd(k);
            ll g = std::gcd(k, m);

            if (S.at(g) < m) {
                prt("YES");
            } else {
                prt("NO");
            }
        }
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
