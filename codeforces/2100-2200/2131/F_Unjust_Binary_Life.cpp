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
    int n;
    rd(n);
    string a, b;
    rd(a, b);

    a = '#' + a;
    b = '#' + b;

    vector<int> a1(n + 1), b1(n + 1);
    for (int i = 1; i <= n; i++) {
        a1[i] = a1[i - 1] + (a[i] == '1');
        b1[i] = b1[i - 1] + (b[i] == '1');
    }

    int ans = 0;
    vector<int> pre_b(n + 1);
    for (int i = 1; i <= n; i++) {
        pre_b[i] = i - 2 * b1[i];
    }

    sort(pre_b.begin() + 1, pre_b.end());
    auto pre = pre_b;

    for (int i = 1; i <= n; i++) {
        pre[i] += pre[i - 1];
    }

    for (int i = 1; i <= n; i++) {
        ans += n * i + n * (n + 1) / 2;

        int cur = 2 * a1[i] - i;
        int j = upper_bound(pre_b.begin() + 1, pre_b.end(), cur) - pre_b.begin();
        int less = (j == 0) ? 0 : pre[j - 1];
        int suf = pre[n] - ((j == 0) ? 0 : pre[j - 1]);
        ans -= (cur * max((j - 1), 0ll) - less + suf - cur * max((n - j + 1), 0ll));
    }

    ans /= 2;

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
