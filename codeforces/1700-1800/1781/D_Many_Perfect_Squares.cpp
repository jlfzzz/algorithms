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
        for (int i = start_index; i < (int) v.size(); i++) {
            read(v[i]);
        }
    }
} // namespace io

using namespace io;

int Multitest = 1;
constexpr int N = int(1e5);

void init() {}

void solve() {
    int n;
    read(n);
    vector<int> a(n);
    read_vec(a);

    ranges::sort(a);

    int ans = 1;
    {
        int cnt0 = 0;
        for (int i = 0; i < n; i++) {
            int r = (int) sqrt((long double) a[i]);
            if (r * r == a[i])
                cnt0++;
        }
        if (cnt0 > ans)
            ans = cnt0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int d = a[j] - a[i];
            for (int k = 1; k * k <= d; k++) {
                if (d % k)
                    continue;
                int x = k;
                int y = d / k;
                if ((y - x) % 2 != 0)
                    continue;
                int dd = x + (y - x) / 2;
                int ee = dd - x;
                int p = max(dd, ee);
                int t = p * p - a[j];
                if (t <= 0)
                    continue;

                int cnt = 0;
                for (int q = 0; q < n; q++) {
                    int r = (int) sqrt((long double) (a[q] + t));
                    if (r * r == a[q] + t)
                        cnt++;
                }
                if (cnt > ans)
                    ans = cnt;
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
        read(T);
    }
    while (T--)
        solve();
    return 0;
}
