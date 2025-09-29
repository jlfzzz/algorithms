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
    int n, q;
    rd(n, q);

    vector<int> a(n + 1);
    rd_vec(a, 1);

    int L, R;
    rd(L, R);

    vector<int> pre1(n + 1), pre2(n + 1);
    for (int i = 1; i <= n; i++) {
        pre1[i] = pre1[i - 1] + a[i];
        pre2[i] = pre2[i - 1] ^ a[i];
    }

    int ans_mx = 0;
    pii ans = {-1, -1};
    for (int i = 1; i <= n; i++) {
        int l = i;
        int r = n + 1;
        int mx = pre1[n] - pre1[i - 1] - (pre2[n] ^ pre2[i - 1]);
        int R = i;

        while (l < r) {
            int mid = (l + r) / 2;

            int sum = pre1[mid] - pre1[i - 1];
            int sum2 = pre2[mid] ^ pre2[i - 1];

            if (sum - sum2 >= mx) {
                r = mid;
                R = mid;
            } else {
                l = mid + 1;
            }
        }

        r = R;
        l = i;
        if (ans.first == -1) {
            ans = {i, r};
            ans_mx = mx;
        } else if (mx == ans_mx) {
            if (r - l + 1 < ans.second - ans.first + 1) {
                ans = {l, r};
            }
        } else if (mx > ans_mx) {
            ans_mx = mx;
            ans = {l, r};
        }
    }

    prt(ans.first, ans.second);
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
