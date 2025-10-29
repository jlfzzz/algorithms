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
    int n;
    rd(n);
    vi a(n + 1);
    rv(a, 1);

    int pos = -1;
    set<int> ans;
    ans.insert(0);
    F(i, 1, n) {
        if (a[i] != -1 && a[i] != 1) {
            pos = i;
            break;
        }
    }

    auto calc = [&](int l, int r) {
        if (l > r) {
            return;
        }
        int mn = a[l];
        int mx = a[l];
        int curMn = a[l], curMx = a[l];
        F(i, l + 1, r) {
            curMn = min(curMn + a[i], a[i]);
            curMx = max(curMx + a[i], a[i]);
            mn = min(mn, curMn);
            mx = max(mx, curMx);
        }

        F(i, mn, mx) { ans.insert(i); }
    };

    if (pos == -1) {
        calc(1, n);
    } else {
        calc(1, pos - 1);
        calc(pos + 1, n);

        int lmn = 0, lmx = 0, s = 0;
        D(i, pos - 1, 1) {
            s += a[i];
            lmn = min(lmn, s);
            lmx = max(lmx, s);
        }

        int rmn = 0, rmx = 0;
        s = 0;
        F(i, pos + 1, n) {
            s += a[i];
            rmn = min(rmn, s);
            rmx = max(rmx, s);
        }

        int L = a[pos] + lmn + rmn;
        int R = a[pos] + lmx + rmx;
        F(i, L, R) { ans.insert(i); }
    }

    prt(SZ(ans));
    for (int x: ans) {
        cout << x << ' ';
    }
    prt("");
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
