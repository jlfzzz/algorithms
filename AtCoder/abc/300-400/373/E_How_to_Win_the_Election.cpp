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
    int N;
    ll M, K;
    rd(N, M, K);

    vl A(N);
    rv(A);

    ll sum_A = 0;
    for (auto x: A)
        sum_A += x;
    ll total_rem = K - sum_A;

    vector<pair<ll, int>> sorted_A(N);
    F(i, 0, N - 1) { sorted_A[i] = {A[i], i}; }

    sort(all(sorted_A), [&](const pair<ll, int> &a, const pair<ll, int> &b) { return a.fi > b.fi; });

    vi pos(N);
    F(i, 0, N - 1) { pos[sorted_A[i].se] = i; }

    vl pref(N + 1, 0);
    F(i, 0, N - 1) { pref[i + 1] = pref[i] + sorted_A[i].fi; }

    vl ans(N);

    F(i, 0, N - 1) {
        ll low = 0, high = total_rem;
        ll res = -1;

        int rk = pos[i];

        while (low <= high) {
            ll X = low + (high - low) / 2;
            ll my_votes = A[i] + X;
            ll rem_votes = total_rem - X;

            int limit_idx = (rk < M) ? M : M - 1;
            auto it = lower_bound(all(sorted_A), make_pair(my_votes, 2 * N),
                                  [&](const pair<ll, int> &a, const pair<ll, int> &b) { return a.fi > b.fi; });
            int split_idx = distance(sorted_A.begin(), it);

            ll cost = 0;
            int L = split_idx;
            int R = limit_idx;

            if (L <= R) {
                ll count = R - L + 1;
                ll sum_range = pref[R + 1] - pref[L];

                if (rk >= L && rk <= R) {
                    count--;
                    sum_range -= sorted_A[rk].fi;
                }

                cost = count * (my_votes + 1) - sum_range;
            }

            if (cost > rem_votes) {
                res = X;
                high = X - 1;
            } else {
                low = X + 1;
            }
        }
        ans[i] = res;
    }

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
