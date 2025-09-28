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
void prt(const vector<T> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        if (i)
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

int Multitest = 1;

void init() {}

void solve() {
    int n;
    cin >> n;

    int t = n;
    while (true) {
        int g = t;

        int tt = t;
        int s = 0;
        while (tt) {
            s += tt % 10;
            tt /= 10;
        }

        if (gcd(g, s) > 1) {
            prt(t);
            return;
        }
        t++;
    }
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
