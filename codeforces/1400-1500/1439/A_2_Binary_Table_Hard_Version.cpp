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

int Multitest = 1;

void init() {}

void solve() {
    int n, m;
    rd(n, m);

    vector<string> a(n);
    for (int i = 0; i < n; i++)
        rd(a[i]);

    vector<array<int, 6>> operations;
    auto add = [&](const array<pair<int, int>, 3> &ps) {
        array<int, 6> line = {ps[0].first + 1,  ps[0].second + 1, ps[1].first + 1,
                              ps[1].second + 1, ps[2].first + 1,  ps[2].second + 1};
        operations.emplace_back(line);
        for (auto [x, y]: ps)
            a[x][y] ^= 1;
    };

    for (int i = n - 1; i > 1; i--) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '1') {
                if (j + 1 < m)
                    add({make_pair(i, j), make_pair(i - 1, j), make_pair(i - 1, j + 1)});
                else
                    add({make_pair(i, j), make_pair(i - 1, j), make_pair(i - 1, j - 1)});
            }
        }
    }

    for (int j = m - 1; j > 1; j--) {
        for (int i = 0; i < 2; i++) {
            if (a[i][j] == '1')
                add({make_pair(i, j), make_pair(0, j - 1), make_pair(1, j - 1)});
        }
    }

    array<pair<int, int>, 4> cell = {make_pair(0, 0), make_pair(0, 1), make_pair(1, 0), make_pair(1, 1)};
    vector<int> p0, p1;
    for (int idx = 0; idx < 4; idx++) {
        auto [x, y] = cell[idx];
        if (a[x][y] == '0')
            p0.push_back(idx);
        else
            p1.push_back(idx);
    }

    if ((int) p1.size() == 4) {
        add({cell[p1[0]], cell[p1[1]], cell[p1[2]]});
        vector<int> np0 = {p1[0], p1[1], p1[2]};
        vector<int> np1 = {p1[3]};
        p0.swap(np0);
        p1.swap(np1);
    }
    if ((int) p1.size() == 1) {
        add({cell[p1[0]], cell[p0[0]], cell[p0[1]]});
        vector<int> np1 = {p0[0], p0[1]};
        vector<int> np0;
        for (size_t k = 2; k < p0.size(); k++)
            np0.push_back(p0[k]);
        np0.push_back(p1[0]);
        p1.swap(np1);
        p0.swap(np0);
    }
    if ((int) p1.size() == 2) {
        add({cell[p1[0]], cell[p0[0]], cell[p0[1]]});
        vector<int> np1;
        np1.push_back(p1[1]);
        np1.insert(np1.end(), p0.begin(), p0.end());
        p1.swap(np1);
    }
    if ((int) p1.size() == 3) {
        add({cell[p1[0]], cell[p1[1]], cell[p1[2]]});
    }

    prt((int) operations.size());
    for (const auto &ln: operations)
        prt(ln[0], ln[1], ln[2], ln[3], ln[4], ln[5]);
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
