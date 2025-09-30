#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
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
        for (int i = start_index; i < (int) v.size(); i++) {
            if (i > start_index)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename End, typename... Args>
    void prt_end(const End &end, const Args &...args) {
        ((cout << args << " "), ...);
        cout << end;
    }

    template<typename... Args>
    void prt_endl(const Args &...args) {
        ((cout << args << " "), ...);
        cout << endl;
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
    void rd_vec(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rd_vec(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }
} // namespace io

using namespace io;

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);

    vector<int> a(1 << n);
    For(i, 1 << n) a[i] = i + 1;

    while (a.size() >= 4) {
        vector<int> nxt;
        for (int i = 0; i + 3 < a.size(); i += 4) {
            int t = a[i], b = a[i + 1], c = a[i + 2], d = a[i + 3];

            prt_endl("?", t, c);
            int res;
            rd(res);

            if (res == 0) {
                prt_endl("?", b, d);
                rd(res);
                if (res == 1) {
                    nxt.push_back(b);
                } else {
                    nxt.push_back(d);
                }
            } else if (res == 1) {
                prt_endl("?", t, d);
                rd(res);
                if (res == 1) {
                    nxt.push_back(t);
                } else {
                    nxt.push_back(d);
                }
            } else {
                prt_endl("?", b, c);
                rd(res);
                if (res == 1) {
                    nxt.push_back(b);
                } else {
                    nxt.push_back(c);
                }
            }
        }
        a.swap(nxt);
    }

    if (a.size() == 1) {
        prt_endl("!", a[0]);
    } else if (a.size() == 2) {
        prt_endl("?", a[0], a[1]);
        int res;
        rd(res);
        if (res == 1) {
            prt_endl("!", a[0]);
        } else {
            prt_endl("!", a[1]);
        }
    } else {
        prt_endl("?", a[0], a[1]);
        int res;
        rd(res);
        if (res == 1) {
            prt_endl("?", a[0], a[2]);
            rd(res);

            if (res == 1) {
                prt_endl("!", a[0]);
            } else {
                prt_endl("!", a[2]);
            }
        } else if (res == 2) {
            prt_endl("?", a[1], a[2]);
            rd(res);

            if (res == 1) {
                prt_endl("!", a[1]);
            } else {
                prt_endl("!", a[2]);
            }
        } else {
            prt_endl("!", a[2]);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--)
        solve();
    return 0;
}
