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

ll rows[255][255];
int masks[255][255];
ll vals[26];
int grid[255][255];

std::mt19937_64 gen(std::random_device{}());
std::uniform_int_distribution<ll> dist(1, 1e13);

vector<ll> manacher(const vector<ll> &a) {
    const ll SEP = -1e15 - 7;
    const ll HEAD = -1e15 - 8;
    const ll TAIL = -1e15 - 9;

    vector<ll> t;
    t.reserve(a.size() * 2 + 3);

    t.push_back(HEAD);
    t.push_back(SEP);
    for (ll x: a) {
        t.push_back(x);
        t.push_back(SEP);
    }
    t.push_back(TAIL);

    ll n = t.size();
    vector<ll> p(n, 0);
    ll center = 0, R = 0;

    for (ll i = 1; i < n - 1; i++) {
        if (i < R) {
            ll mirror = 2 * center - i;
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
    F(i, 0, 25) { vals[i] = dist(gen); }

    int n, m;
    rd(n, m);

    F(i, 1, n) {
        F(j, 1, m) {
            char c;
            rd(c);

            grid[i][j] = c - 'a';
        }
    }

    F(i, 1, n) {
        F(j, 1, m) {
            rows[i][j] = rows[i][j - 1] + vals[grid[i][j]];
            masks[i][j] = masks[i][j - 1] ^ (1 << grid[i][j]);
        }
    }

    ll ans = 0;
    F(l, 1, m) {
        F(r, l, m) {
            vl temp;

            auto calc = [&]() {
                auto p = manacher(temp);
                for (ll rad: p) {
                    ans += rad / 2;
                }
                temp.clear();
            };

            F(row, 1, n) {
                int mask = masks[row][r] ^ masks[row][l - 1];
                if (popcount((us) mask) > 1) {
                    calc();
                } else {
                    temp.pb(rows[row][r] - rows[row][l - 1]);
                }
            }

            calc();
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
