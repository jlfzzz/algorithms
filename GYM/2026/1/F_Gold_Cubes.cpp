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

int Multitest = 1;

void init() {}

void solve() {
    int v;
    rd(v);

    vi a(3);
    rv(a);

    vi b(3);
    rv(b);

    struct S {
        ll x, y, z, val, st;
    };

    vector<S> items;
    F(nx, 0, b[0]) {
        F(ny, 0, b[1]) {
            if (nx + ny > 180)
                break;
            F(nz, 0, b[2]) {
                if (nx + ny + nz > 180)
                    break;
                if (nx + ny + nz == 0)
                    continue;
                ll weight = (ll) nx * a[0] + (ll) ny * a[1] + (ll) nz * a[2];

                if (weight >= 100) {
                    bool minimal = true;
                    if (nx > 0 && (nx - 1) * a[0] + ny * a[1] + nz * a[2] >= 100)
                        minimal = false;
                    if (ny > 0 && nx * a[0] + (ny - 1) * a[1] + nz * a[2] >= 100)
                        minimal = false;
                    if (nz > 0 && nx * a[0] + ny * a[1] + (nz - 1) * a[2] >= 100)
                        minimal = false;
                    if (minimal) {
                        ll prof = (ll) v * 100 - weight * 5;
                        if (prof > 0)
                            items.pb(S{(ll) nx, (ll) ny, (ll) nz, prof, 0});
                    }
                }

                // 检查是否为极小组合 (st=1)
                ll target_win = max(100LL, 20LL * v + 1);
                if (weight >= target_win) {
                    bool minimal = true;
                    if (nx > 0 && (nx - 1) * a[0] + ny * a[1] + nz * a[2] >= target_win)
                        minimal = false;
                    if (ny > 0 && nx * a[0] + (ny - 1) * a[1] + nz * a[2] >= target_win)
                        minimal = false;
                    if (nz > 0 && nx * a[0] + ny * a[1] + (nz - 1) * a[2] >= target_win)
                        minimal = false;
                    if (minimal) {
                        ll prof = (ll) v * 100 - weight * 5;
                        items.pb(S{(ll) nx, (ll) ny, (ll) nz, prof, 1});
                    }
                }
            }
        }
    }

    // 2. 四维 DP 刷表更新
    // dp[x][y][z][0]: 尚未包含中奖盒
    // dp[x][y][z][1]: 已包含至少一个中奖盒
    static ll dp[181][181][181][2];
    F(i, 0, b[0]) F(j, 0, b[1]) F(k, 0, b[2]) dp[i][j][k][0] = dp[i][j][k][1] = -INF;

    dp[0][0][0][0] = 0;

    for (auto &it: items) {
        if (it.st == 0) {
            // 普通盒：完全背包更新 (正向刷表)
            F(i, 0, b[0] - it.x) {
                F(j, 0, b[1] - it.y) {
                    if (i + j + it.x + it.y > 180)
                        break;
                    F(k, 0, b[2] - it.z) {
                        if (i + j + k + it.x + it.y + it.z > 180)
                            break;
                        if (dp[i][j][k][0] > -INF)
                            dp[i + it.x][j + it.y][k + it.z][0] =
                                max(dp[i + it.x][j + it.y][k + it.z][0], dp[i][j][k][0] + it.val);
                        if (dp[i][j][k][1] > -INF)
                            dp[i + it.x][j + it.y][k + it.z][1] =
                                max(dp[i + it.x][j + it.y][k + it.z][1], dp[i][j][k][1] + it.val);
                    }
                }
            }
        } else {
            // 中奖盒：状态 0 转移至 1 (为了保证至少一个，逆向更新或仅更新0->1)
            D(i, b[0] - it.x, 0) {
                D(j, b[1] - it.y, 0) {
                    if (i + j + it.x + it.y > 180)
                        continue;
                    D(k, b[2] - it.z, 0) {
                        if (i + j + k + it.x + it.y + it.z > 180)
                            continue;
                        if (dp[i][j][k][0] > -INF)
                            dp[i + it.x][j + it.y][k + it.z][1] =
                                max(dp[i + it.x][j + it.y][k + it.z][1], dp[i][j][k][0] + it.val);
                    }
                }
            }
        }
    }

    // 3. 统计结果
    ll ans = 0;
    F(i, 0, b[0]) F(j, 0, b[1]) F(k, 0, b[2]) ans = max(ans, dp[i][j][k][1]);
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
