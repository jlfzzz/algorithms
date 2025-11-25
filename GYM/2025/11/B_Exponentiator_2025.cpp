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

#ifdef WOAIHUTAO
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int MAXV = 1000005;
int spf[MAXV];
bool has_rad[MAXV];
bool can_cover[MAXV];

void init() {
    iota(spf, spf + MAXV, 0);
    for (int i = 2; i * i < MAXV; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAXV; j += i)
                if (spf[j] == j)
                    spf[j] = i;
        }
    }
}

int get_rad(int n) {
    int res = 1;
    while (n > 1) {
        int p = spf[n];
        res *= p;
        while (n % p == 0)
            n /= p;
    }
    return res;
}

ll capped_pow(ll base, ll exp) {
    ll res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
        if (res >= 30)
            return 30;
    }
    return res;
}

ll solve_small_tower(vector<int> nums) {
    if (nums.empty())
        return 1;
    sort(all(nums));
    ll max_val = 0;
    do {
        ll cur = nums.back();
        for (int i = (int) nums.size() - 2; i >= 0; i--) {
            cur = capped_pow(nums[i], cur);
        }
        max_val = max(max_val, cur);
        if (max_val >= 30)
            return 30;
    } while (next_permutation(all(nums)));
    return max_val;
}

int Multitest = 0;

void solve() {
    int n, q;
    rd(n, q);
    vi a;
    for (int i = 0; i < n; ++i) {
        int x;
        rd(x);
        if (x >= 2)
            a.pb(x);
    }

    bool big_mode = (SZ(a) >= 7);
    if (big_mode) {
        for (int x: a) {
            has_rad[get_rad(x)] = true;
        }
        for (int i = 1; i < MAXV; i++) {
            if (has_rad[i]) {
                for (int j = 1; j * j <= i; j++) {
                    if (i % j == 0) {
                        can_cover[j] = true;
                        if (j * j != i)
                            can_cover[i / j] = true;
                    }
                }
            }
        }
    }

    while (q--) {
        int x;
        rd(x);
        if (x == 1) {
            prt("Yes");
            continue;
        }
        if (a.empty()) {
            prt("No");
            continue;
        }

        if (big_mode) {
            if (can_cover[get_rad(x)])
                prt("Yes");
            else
                prt("No");
        } else {
            bool possible = false;

            vp facts;
            int temp_x = x;
            while (temp_x > 1) {
                int p = spf[temp_x];
                int cnt = 0;
                while (temp_x % p == 0) {
                    temp_x /= p;
                    cnt++;
                }
                facts.pb(p, cnt);
            }

            for (int i = 0; i < SZ(a); i++) {
                int base = a[i];
                bool base_ok = true;
                ll needed_exp = 1;

                for (auto &[p, cnt]: facts) {
                    if (base % p != 0) {
                        base_ok = false;
                        break;
                    }
                    int b_cnt = 0;
                    int tmp = base;
                    while (tmp % p == 0) {
                        tmp /= p;
                        b_cnt++;
                    }
                    needed_exp = max(needed_exp, (ll) (cnt + b_cnt - 1) / b_cnt);
                }

                if (!base_ok)
                    continue;

                if (needed_exp == 1) {
                    possible = true;
                    break;
                }

                vi remaining;
                for (int j = 0; j < SZ(a); ++j)
                    if (i != j)
                        remaining.pb(a[j]);

                if (solve_small_tower(remaining) >= needed_exp) {
                    possible = true;
                    break;
                }
            }
            if (possible)
                prt("Yes");
            else
                prt("No");
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
