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

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

void solve() {
    int n, m;
    rd(n, m);
    vi x(n + 1), y(m + 1);
    rv(x, 1), rv(y, 1);

    unordered_map<int, pii> mp;
    unordered_set<int> col, row;
    set<pii> pos;
    F(i, 1, n) { mp[x[i]] = {i, -1}; }
    F(i, 1, m) {
        auto it = mp.find(y[i]);
        if (it == mp.end()) {
            mp[y[i]] = {-1, i};
        } else {
            it->second.second = i;
        }
    }

    vvi ans(n + 1, vi(m + 1));
    D(i, n * m, 1) {
        auto it = mp.find(i);

        if (it == mp.end()) {
            if (pos.empty()) {
                prt("No");
                return;
            }
            auto [r, c] = *pos.begin();
            pos.erase(pos.begin());
            ans[r][c] = i;
        } else {
            auto [xx, yy] = it->second;

            if (xx != -1 && yy != -1) {
                if (ans[xx][yy]) {
                    prt("No");
                    return;
                }
                ans[xx][yy] = i;

                for (auto c: col) {
                    pos.insert({xx, c});
                }
                for (auto r: row) {
                    pos.insert({r, yy});
                }

                row.insert(xx);
                col.insert(yy);

            } else if (xx != -1) {
                if (col.empty()) {
                    prt("No");
                    return;
                }
                int pick_col = *col.begin();
                if (ans[xx][pick_col]) {
                    prt("No");
                    return;
                }
                ans[xx][pick_col] = i;
                for (auto c: col) {
                    if (c != pick_col) {
                        pos.insert({xx, c});
                    }
                }
                row.insert(xx);

            } else {
                if (row.empty()) {
                    prt("No");
                    return;
                }
                int pick_row = *row.begin();
                if (ans[pick_row][yy]) {
                    prt("No");
                    return;
                }
                ans[pick_row][yy] = i;

                for (auto r: row) {
                    if (r != pick_row) {
                        pos.insert({r, yy});
                    }
                }
                col.insert(yy);
            }
        }
    }

    prt("Yes");
    F(i, 1, n) {
        F(j, 1, m) { cout << ans[i][j] << (j == m ? "" : " "); }
        cout << "\n";
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
