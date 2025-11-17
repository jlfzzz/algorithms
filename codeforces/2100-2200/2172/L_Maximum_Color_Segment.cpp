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
    int n, m, k;
    rd(n, m, k);
    string s;
    rd(s);

    vi T(n - 1);
    F(i, 0, n - 2) { T[i] = (s[i] != s[i + 1]); }

    vi dpBest(m + 1, -inf);
    dpBest[0] = 0;
    vvi cur(m + 2, vi(2));
    vvi nxt(m + 2, vi(2));
    vi ndp(m + 1);
    F(r, 0, k - 1) {
        vi vals;
        vi idx;
        for (int i = r; i < n - 1; i += k) {
            vals.pb(T[i]);
            idx.pb(i);
        }

        if (vals.empty())
            continue;

        int len = SZ(vals);
        bool allow_start = (idx[0] == k - 1);
        bool allow_end = (idx.back() == n - k - 1);

        int max_c = min(m, len + 2);
        F(c, 0, max_c) {
            cur[c][0] = -inf;
            cur[c][1] = -inf;
        }

        cur[0][0] = 0;
        if (allow_start && max_c >= 1) {
            cur[1][1] = 0;
        }
        F(i, 0, len - 1) {
            int limit = min(m, max_c + 1);
            F(c, 0, limit) {
                nxt[c][0] = -inf;
                nxt[c][1] = -inf;
            }

            F(c, 0, max_c) {
                F(prev_op, 0, 1) {
                    if (cur[c][prev_op] == -inf)
                        continue;

                    F(next_op, 0, 1) {
                        if (i == len - 1) {
                            if (next_op == 1 && !allow_end)
                                continue;
                        }

                        int new_c = c + next_op;
                        if (new_c > m)
                            continue;

                        int val = vals[i] ^ prev_op ^ next_op;
                        if (nxt[new_c][next_op] < cur[c][prev_op] + val) {
                            nxt[new_c][next_op] = cur[c][prev_op] + val;
                        }
                    }
                }
            }
            swap(cur, nxt);
            max_c = min(m, max_c + 1);
        }
        F(j, 0, m) ndp[j] = -inf;

        F(c, 0, max_c) {
            int gain = max(cur[c][0], cur[c][1]);
            if (gain == -inf)
                continue;
            F(j, 0, m - c) {
                if (dpBest[j] != -inf) {
                    if (ndp[j + c] < dpBest[j] + gain) {
                        ndp[j + c] = dpBest[j] + gain;
                    }
                }
            }
        }
        dpBest = ndp;
    }

    int ans = 0;
    F(j, 0, m) { ans = max(ans, dpBest[j]); }
    prt(ans + 1);
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
