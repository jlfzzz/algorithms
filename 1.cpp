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
    vi x(n), y(m);
    rv(x), rv(y);
    int tot = n * m;
    vi rowOf(tot + 1, -1), colOf(tot + 1, -1);
    F(i, 0, n - 1) {
        int v = x[i];
        if (rowOf[v] != -1) {
            prt("No");
            return;
        }
        rowOf[v] = i;
    }
    F(j, 0, m - 1) {
        int v = y[j];
        if (colOf[v] != -1) {
            prt("No");
            return;
        }
        colOf[v] = j;
    }

    vvp bucket(tot + 1);
    F(i, 0, n - 1) {
        F(j, 0, m - 1) {
            int t = min(x[i], y[j]);
            bucket[t].pb(i, j);
        }
    }
    vvi ans(n, vi(m));

    vector<set<int>> rowCells(n), colCells(m);
    set<int> rowS;
    D(v, tot, 1) {
        for (auto &p: bucket[v]) {
            int r = p.first;
            int c = p.second;
            rowCells[r].insert(c);
            colCells[c].insert(r);
            rowS.insert(r);
        }
        int r = rowOf[v];
        int c = colOf[v];
        if (r != -1 && c != -1) {
            if (!rowCells[r].count(c)) {
                prt("No");
                return;
            }
            ans[r][c] = v;
            rowCells[r].erase(c);
            colCells[c].erase(r);
            if (rowCells[r].empty()) {
                rowS.erase(r);
            }
        } else if (r != -1) {
            if (rowCells[r].empty()) {
                prt("No");
                return;
            }
            int cj = *rowCells[r].begin();
            ans[r][cj] = v;
            rowCells[r].erase(cj);
            colCells[cj].erase(r);
            if (rowCells[r].empty()) {
                rowS.erase(r);
            }
        } else if (c != -1) {
            if (colCells[c].empty()) {
                prt("No");
                return;
            }
            int ri = *colCells[c].begin();
            ans[ri][c] = v;
            colCells[c].erase(ri);
            rowCells[ri].erase(c);
            if (rowCells[ri].empty()) {
                rowS.erase(ri);
            }
        } else {
            if (rowS.empty()) {
                prt("No");
                return;
            }
            int ri = *rowS.begin();
            int cj = *rowCells[ri].begin();
            ans[ri][cj] = v;
            rowCells[ri].erase(cj);
            colCells[cj].erase(ri);
            if (rowCells[ri].empty()) {
                rowS.erase(ri);
            }
        }
    }
    prt("Yes");
    F(i, 0, n - 1) {
        F(j, 0, m - 1) { cout << ans[i][j] << (j + 1 == m ? '\n' : ' '); }
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
