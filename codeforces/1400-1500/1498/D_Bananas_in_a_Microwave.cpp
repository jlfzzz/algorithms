#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

namespace io {
    void debug() { cerr << "\n"; }

    template<typename T, typename... Args>
    void debug(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        debug(args...);
    }

    template<typename... Args>
    void prt(const Args &...args) {
        ((cout << args << " "), ...);
        cout << "\n";
    }

    template<typename T>
    void prt_vec(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prt_vec(const vector<T> &v, int start_index) {
        for (int i = start_index; i < v.size(); i++) {
            if (i > start_index)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename... Args>
    void prt_end(const string &end, const Args &...args) {
        ((cout << args << " "), ...);
        cout << end;
    }

    template<typename T>
    void read(T &x) {
        cin >> x;
    }

    template<typename T, typename... Args>
    void read(T &x, Args &...args) {
        cin >> x;
        read(args...);
    }

    template<typename A, typename B>
    void read(pair<A, B> &p) {
        cin >> p.first >> p.second;
    }

    template<typename T>
    void read_vec(vector<T> &v) {
        for (auto &x: v) {
            read(x);
        }
    }

    template<typename T>
    void read_vec(vector<T> &v, int start_index) {
        for (int i = start_index; i < v.size(); i++) {
            read(v[i]);
        }
    }
} // namespace io

using namespace io;

int Multitest = 0;

void init() {}

void solve() {
    int n, m;
    read(n, m);

    const int lim = 100000;

    vector<int> ans(m + 1, -1);
    vector<bool> cur(m + 1), nxt(m + 1);
    cur[0] = true;

    For(i, n) {
        int op, x, y;
        read(op, x, y);

        fill(nxt.begin(), nxt.end(), false);

        if (op == 1) {
            int add = (x + lim - 1) / lim;
            vector<int> rem(m + 1, -1);

            for (int k = 0; k <= m; k++) {
                if (cur[k]) {
                    rem[k] = y;
                }
            }

            for (int k = 0; k <= m; k++) {
                if (cur[k])
                    nxt[k] = true;
            }

            for (int k = add; k <= m; k++) {
                if (rem[k - add] > 0) {
                    nxt[k] = true;
                    rem[k] = max(rem[k], rem[k - add] - 1);
                }
            }
        } else {
            vector<int> temp(m + 1, -1);
            for (int k = 0; k <= m; k++) {
                if (cur[k])
                    temp[k] = y;
            }

            for (int v = 0; v <= m; v++) {
                if (temp[v] >= 0)
                    nxt[v] = true;
                if (v == 0)
                    continue;
                if (temp[v] > 0) {
                    i128 prod = (i128) v * (i128) x + (lim - 1);
                    int t = (prod / lim);
                    if (t <= m)
                        temp[t] = max(temp[t], temp[v] - 1);
                }
            }
        }

        cur.swap(nxt);
        for (int j = 1; j <= m; j++)
            if (ans[j] == -1 && cur[j])
                ans[j] = i + 1;
    }

    prt_vec(ans, 1);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        cin >> T;
    }
    while (T--)
        solve();
    return 0;
}
