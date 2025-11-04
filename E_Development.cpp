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
    int n, m;
    rd(n, m);
    vvl dis(n + 1, vl(n + 1, INF));
    F(i, 1, n) dis[i][i] = 0;
    F(i, 1, m) {
        int a, b;
        ll c;
        rd(a, b, c);
        if (c < dis[a][b]) {
            dis[a][b] = dis[b][a] = c;
        }
    }

    int k, T;
    rd(k, T);
    vi isAirport(n + 1, 0);
    vector<int> airports;
    F(i, 1, k) {
        int x;
        rd(x);
        if (!isAirport[x]) {
            isAirport[x] = 1;
            airports.pb(x);
        }
    }
    for (int ii = 0; ii < (int) airports.size(); ++ii) {
        for (int jj = ii + 1; jj < (int) airports.size(); ++jj) {
            int u = airports[ii], v = airports[jj];
            if (T < dis[u][v])
                dis[u][v] = dis[v][u] = T;
        }
    }
    F(kv, 1, n) {
        F(i, 1, n) {
            if (dis[i][kv] == INF)
                continue;
            F(j, 1, n) {
                ll cand = dis[i][kv] + dis[kv][j];
                if (cand < dis[i][j])
                    dis[i][j] = cand;
            }
        }
    }

    int q;
    rd(q);

    while (q--) {
        int op;
        rd(op);

        if (op == 1) {
            int x, y, t;
            rd(x, y, t);
            vl dx(n + 1), dy(n + 1), rx(n + 1), ry(n + 1);
            F(i, 1, n) {
                dx[i] = dis[i][x];
                dy[i] = dis[i][y];
            }
            F(j, 1, n) {
                rx[j] = dis[x][j];
                ry[j] = dis[y][j];
            }
            F(i, 1, n) {
                F(j, 1, n) {
                    ll v1 = dx[i] + (ll) t + ry[j];
                    if (v1 < dis[i][j])
                        dis[i][j] = v1;
                    ll v2 = dy[i] + (ll) t + rx[j];
                    if (v2 < dis[i][j])
                        dis[i][j] = v2;
                }
            }
        } else if (op == 2) {
            int x;
            rd(x);
            if (!isAirport[x]) {
                vector<int> S;
                S.reserve(n);
                F(i, 1, n) if (isAirport[i]) S.pb(i);
                if (!S.empty()) {
                    vl dNear(n + 1, INF);
                    for (int v: S) {
                        F(i, 1, n) {
                            if (dis[i][v] < dNear[i])
                                dNear[i] = dis[i][v];
                        }
                    }
                    F(i, 1, n) {
                        ll cand = dNear[i] + (ll) T;
                        if (cand < dis[i][x])
                            dis[i][x] = cand;
                        if (cand < dis[x][i])
                            dis[x][i] = cand;
                    }
                    F(i, 1, n) {
                        if (dis[i][x] == INF)
                            continue;
                        F(j, 1, n) {
                            ll cand = dis[i][x] + dis[x][j];
                            if (cand < dis[i][j])
                                dis[i][j] = cand;
                        }
                    }
                }
                isAirport[x] = 1;
            } else {
            }
        } else {
            ll ans = 0;
            F(i, 1, n) {
                F(j, 1, n) {
                    if (dis[i][j] < INF / 4)
                        ans += dis[i][j];
                }
            }
            prt(ans);
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
