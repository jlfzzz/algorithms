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

void solve() {
    int n, m, l;
    rd(n, m, l);

    struct Card {
        int val, owner;
    };
    vector<Card> a;
    a.reserve(n + m + l);

    F(i, 0, n - 1) {
        int x;
        rd(x);
        a.pb(Card{x, 1});
    }
    F(i, 0, m - 1) {
        int x;
        rd(x);
        a.pb(Card{x, 2});
    }
    F(i, 0, l - 1) {
        int x;
        rd(x);
        a.pb(Card{x, 0});
    }


    sort(all(a), [](const Card &x, const Card &y) { return x.val < y.val; });

    int k = n + m + l;
    vi p3(k + 1);
    p3[0] = 1;
    F(i, 1, k) p3[i] = p3[i - 1] * 3;

    int init_mask = 0;
    F(i, 0, k - 1) { init_mask += a[i].owner * p3[i]; }

    vvi memo(p3[k], vi(2, -1));

    auto get_owner = [&](int mask, int idx) { return (mask / p3[idx]) % 3; };

    auto set_owner = [&](int mask, int idx, int v) {
        int old = (mask / p3[idx]) % 3;
        return mask + (v - old) * p3[idx];
    };

    auto dfs = [&](this auto &&dfs, int mask, int turn) -> int {
        if (memo[mask][turn] != -1)
            return memo[mask][turn];

        int player = (turn == 0 ? 1 : 2);

        F(i, 0, k - 1) {
            if (get_owner(mask, i) == player) {
                int nxt_mask = set_owner(mask, i, 0);

                if (!dfs(nxt_mask, 1 - turn)) {
                    return memo[mask][turn] = 1;
                }
                F(j, 0, i - 1) {
                    if (get_owner(mask, j) == 0 && a[j].val < a[i].val) {
                        int nxt_mask_take = set_owner(nxt_mask, j, player);
                        if (!dfs(nxt_mask_take, 1 - turn)) {
                            return memo[mask][turn] = 1;
                        }
                    }
                }
            }
        }

        return memo[mask][turn] = 0;
    };

    if (dfs(init_mask, 0)) {
        prt("Takahashi");
    } else {
        prt("Aoki");
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
