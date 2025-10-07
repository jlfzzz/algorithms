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
constexpr int MOD2 = int(998244353);
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
    int n, k;
    rd(n, k);

    vector<int> a(n), b(k);
    rd_vec(a);
    rd_vec(b);

    map<int, pii> cnt;

    int ans = 1;
    map<int, int> idx;

    for (int i = 0; i < n; i++) {
        idx[a[i]] = i;
    }

    set<int> suf;
    for (int x: b) {
        suf.insert(x);
    }

    for (int i = 0; i < k; i++) {
        int cur = b[i];
        suf.erase(cur);

        if (!idx.contains(cur)) {
            prt(0);
            return;
        }

        int j = idx[cur];

        if (j + 1 < n) {
            int nxt = a[j + 1];
            if (!suf.contains(nxt)) {
                cnt[cur].second = 1;
            }
        }

        if (j - 1 >= 0) {
            int pre = a[j - 1];
            if (!suf.contains(pre)) {
                cnt[cur].first = 1;
            }
        }

        if (!cnt.contains(cur)) {
            prt(0);
            return;
        }
    }

    for (int i = 0; i < k; i++) {
        int target = b[i];
        auto [pre, nxt] = cnt[target];

        if (pre + nxt == 2) {
            ans = ans * 2 % MOD2;
        } else {
            int j = idx[target];
            if (pre) {
                if (j + 1 < n) {
                    int x = a[j + 1];
                    cnt[x].first = 1;
                }
            } else {
                if (j - 1 >= 0) {
                    int x = a[j - 1];
                    cnt[x].second = 1;
                }
            }
        }
    }

    prt(ans);
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
