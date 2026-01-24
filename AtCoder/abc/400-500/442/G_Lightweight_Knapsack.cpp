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
    ll n, c;
    rd(n, c);

    vvp a(4);
    F(i, 1, n) {
        ll w, v, k;
        rd(w, v, k);
        a[w].pb(v, k);
    }

    for (auto &v: a) {
        ranges::sort(v, greater<>());
    }

    vvp b(4);
    vector<vector<i128>> pref(4), cnt(4);
    F(i, 1, 3) {
        for (auto [v, k]: a[i]) {
            if (b[i].empty() || v != b[i].back().first) {
                b[i].pb(v, k);
            } else {
                b[i].back().second += k;
            }
        }

        int m = SZ(b[i]);
        pref[i].assign(m + 1, 0);
        cnt[i].assign(m + 1, 0);

        F(j, 0, m - 1) {
            pref[i][j + 1] = pref[i][j] + (i128) b[i][j].first * (i128) b[i][j].second;
            cnt[i][j + 1] = cnt[i][j] + (i128) b[i][j].second;
        }
    }

    auto get_sum = [&](int id, i128 k) -> i128 {
        if (k <= 0)
            return 0;
        if (cnt[id].empty())
            return 0;
        if (cnt[id].back() == 0)
            return 0;
        if (k >= cnt[id].back())
            return pref[id].back();

        int idx = (int) (ranges::upper_bound(cnt[id], k) - cnt[id].begin() - 1); // idx in [0..m-1]
        i128 res = pref[id][idx];
        i128 rem = k - cnt[id][idx];
        if (rem > 0)
            res += rem * (i128) b[id][idx].first;
        return res;
    };

    const i128 neg_inf = -((i128) 1 << 120);

    auto check3 = [&](i128 c3) -> i128 {
        i128 rem = (i128) c - c3 * 3;
        if (rem < 0)
            return neg_inf;

        i128 lo2 = 0, hi2 = 0;
        if (!cnt[2].empty())
            hi2 = min(cnt[2].back(), rem / 2);

        auto check2 = [&](i128 c2) -> i128 {
            i128 rem1 = rem - c2 * 2;
            if (rem1 < 0)
                return neg_inf;
            i128 take1 = 0;
            if (!cnt[1].empty())
                take1 = min(cnt[1].back(), rem1);
            return get_sum(2, c2) + get_sum(1, take1);
        };

        while (lo2 + 5 < hi2) {
            i128 m1 = lo2 + (hi2 - lo2) / 3;
            i128 m2 = hi2 - (hi2 - lo2) / 3;

            if (check2(m1) < check2(m2)) {
                lo2 = m1;
            } else {
                hi2 = m2;
            }
        }

        i128 best12 = 0;
        for (i128 x = lo2; x <= hi2; x++) {
            best12 = max(best12, check2(x));
        }

        return get_sum(3, c3) + best12;
    };

    i128 lo3 = 0, hi3 = 0;
    if (!cnt[3].empty())
        hi3 = min(cnt[3].back(), (i128) c / 3);

    while (lo3 + 5 < hi3) {
        i128 mid1 = lo3 + (hi3 - lo3) / 3;
        i128 mid2 = hi3 - (hi3 - lo3) / 3;

        if (check3(mid1) < check3(mid2)) {
            lo3 = mid1;
        } else {
            hi3 = mid2;
        }
    }

    i128 ans = 0;
    for (i128 x = lo3; x <= hi3; x++) {
        ans = max(ans, check3(x));
    }

    auto print_i128 = [&](i128 x) {
        if (x == 0) {
            cout << 0;
            return;
        }
        if (x < 0) {
            cout << '-';
            x = -x;
        }
        string s;
        while (x) {
            int d = (int) (x % 10);
            s.push_back(char('0' + d));
            x /= 10;
        }
        reverse(all(s));
        cout << s;
    };

    print_i128(ans);
    cout << '\n';
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
