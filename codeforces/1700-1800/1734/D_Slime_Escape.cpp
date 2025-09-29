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
        for (int i = start_index; i < (int) v.size(); i++) {
            read(v[i]);
        }
    }
} // namespace io

using namespace io;

int Multitest = 1;

void init() {}

void solve() {
    int n, k;
    read(n, k);

    vector<int> a(n + 1);
    read_vec(a, 1);

    if (a[k] < 0) {
        prt("NO");
        return;
    }

    vector<int> s(n + 2);
    s[k - 1] = a[k - 1];
    s[k + 1] = a[k + 1];
    s[k] = 0;

    for (int i = k - 2; i >= 1; i--)
        s[i] = s[i + 1] + a[i];
    for (int i = k + 2; i <= n; i++)
        s[i] = s[i - 1] + a[i];

    int l = k - 1, r = k + 1;
    int s1 = a[k], s2 = a[k];
    int ll, rr;

    while (l > 0 && r <= n) {
        ll = l;
        rr = r;

        while (l > 0 && s[l] + s2 >= 0) {
            s1 = max(s1, a[k] + s[l]);
            l--;
        }

        while (r <= n && s[r] + s1 >= 0) {
            s2 = max(s2, a[k] + s[r]);
            r++;
        }

        if (ll == l && rr == r) {
            prt("NO");
            return;
        }
    }

    prt("YES");
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        read(T);
    }
    while (T--)
        solve();
    return 0;
}
