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

int Multitest = 1;

void init() {}

void solve() {
    int n, m;
    rd(n, m);
    vector<string> s(n), t(n);
    rv(s);
    rv(t);

    if (s == t) {
        prt(0);
        return;
    }

    struct Op {
        int r1, c1, r2, c2;
    };
    vector<Op> ans;

    auto apply = [&](int r1, int c1, int r2, int c2) {
        ans.pb(r1 + 1, c1 + 1, r2 + 1, c2 + 1);
        auto toggle = [&](char &c) { c = (c == '#' ? '.' : '#'); };
        toggle(s[r1][c1]);
        toggle(s[r2][c2]);
    };

    vector<vector<bool>> fixed(n, vector<bool>(m, false));
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    F(i, 0, n - 1) {
        F(j, 0, m - 1) {
            if (i == n - 1 && j == m - 1)
                continue;

            if (s[i][j] == t[i][j]) {
                fixed[i][j] = true;
                continue;
            }

            int ni = i, nj = j;
            if (j + 1 < m)
                nj = j + 1;
            else
                ni = i + 1;

            if (s[i][j] == s[ni][nj]) {
                apply(i, j, ni, nj);
                fixed[i][j] = true;
            }
            else {
                queue<pair<int, int>> q;
                q.push({ni, nj});

                vector<vector<pair<int, int>>> par(n, vector<pair<int, int>>(m, {-1, -1}));
                par[ni][nj] = {-2, -2};

                int start_r = -1, start_c = -1;
                int anchor_r = -1, anchor_c = -1;

                bool found = false;
                while (!q.empty()) {
                    auto [cr, cc] = q.front();
                    q.pop();
                    
                    F(k, 0, 3) {
                        int nr = cr + dr[k];
                        int nc = cc + dc[k];

                        if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                            continue;
                        if (fixed[nr][nc])
                            continue;
                        if (nr == i && nc == j)
                            continue;
                        if (s[cr][cc] == s[nr][nc]) {
                            start_r = cr;
                            start_c = cc;
                            anchor_r = nr;
                            anchor_c = nc;
                            found = true;
                            goto BFS_END;
                        }


                        if (par[nr][nc].first == -1) {
                            par[nr][nc] = {cr, cc};
                            q.push({nr, nc});
                        }
                    }
                }
            BFS_END:;

                if (!found) {
                    prt(-1);
                    return;
                }
                apply(start_r, start_c, anchor_r, anchor_c);
                int cur_r = start_r, cur_c = start_c;
                while (cur_r != ni || cur_c != nj) {
                    auto [pr, pc] = par[cur_r][cur_c];
                    apply(cur_r, cur_c, pr, pc);
                    cur_r = pr;
                    cur_c = pc;
                }
                apply(i, j, ni, nj);
                fixed[i][j] = true;
            }
        }
    }

    if (s[n - 1][m - 1] != t[n - 1][m - 1]) {
        prt(-1);
    } else {
        prt(SZ(ans));
        for (auto &op: ans) {
            cout << op.r1 << " " << op.c1 << " " << op.r2 << " " << op.c2 << "\n";
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
