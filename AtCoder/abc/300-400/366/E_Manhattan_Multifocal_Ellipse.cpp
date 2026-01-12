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
    int n, d;
    rd(n, d);

    vi ys, xs(9e6);
    const int offset = 4e6;
    ll tot_x = 0;

    int min_x = inf, max_x = -inf;

    F(i, 1, n) {
        int x, y;
        rd(x, y);
        ys.pb(y);
        xs[x + offset]++;
        tot_x += x;
        min_x = min(min_x, x);
        max_x = max(max_x, x);
    }

    ranges::sort(ys);
    vl pref(n);
    pref[0] = ys[0];
    F(i, 1, n - 1) { pref[i] = pref[i - 1] + ys[i]; }

    auto calc_y_cost = [&](ll y_val) -> ll {
        int idx = lower_bound(all(ys), y_val) - ys.begin();
        ll sum_left = (idx > 0 ? pref[idx - 1] : 0);
        ll cost_left = (ll) idx * y_val - sum_left;
        ll sum_right = pref[n - 1] - sum_left;
        ll cost_right = sum_right - (ll) (n - idx) * y_val;
        return cost_left + cost_right;
    };

    ll pre = 0;
    ll cnt = 0;
    vl suf(9e6 + 56);

    D(i, 4e6, -4e6) { suf[i + offset] = suf[i + offset + 1] + xs[i + offset]; }

    ll ans = 0;
    int SEARCH_L = max(-4000000, min_x - d - 5);
    int SEARCH_R = min(4000000, max_x + d + 5);

    F(i, -4e6, 4e6) {
        pre += (ll) xs[i + offset] * i;
        cnt += xs[i + offset];

        if (i < SEARCH_L || i > SEARCH_R)
            continue;

        ll dx = cnt * i - pre + (tot_x - pre) - (n - cnt) * (ll) i;

        if (dx > d)
            continue;

        ll rem = d - dx;
        ll mid_y = ys[n / 2];
        if (calc_y_cost(mid_y) > rem)
            continue;

        ll L, R;
        ll valid_L = mid_y;

        ll range_bound = rem; 

        L = mid_y - range_bound - 5;
        if (L < -2e6)
            L = -2e6; 
        R = mid_y;

        while (L <= R) {
            ll mid = L + (R - L) / 2;
            if (calc_y_cost(mid) <= rem) {
                valid_L = mid;
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }

        ll valid_R = mid_y;
        L = mid_y;
        R = mid_y + range_bound + 5;
        if (R > 2e6)
            R = 2e6;

        while (L <= R) {
            ll mid = L + (R - L) / 2;
            if (calc_y_cost(mid) <= rem) {
                valid_R = mid;
                L = mid + 1;
            } else {
                R = mid - 1;
            }
        }

        ans += (valid_R - valid_L + 1);
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
