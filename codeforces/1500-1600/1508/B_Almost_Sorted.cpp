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
    static const long long LIM = (long long) 2e18;
    static const int MAXN = 100000 + 5;
    static vector<long long> ways; // ways[m] = number of valid completions for length m: 2^{m-1} (m>=1), ways[0]=1
    if (ways.empty()) {
        ways.assign(MAXN, 0);
        ways[0] = 1;
        if (MAXN >= 2)
            ways[1] = 1;
        for (int i = 2; i < MAXN; i++) {
            if (LIM / 2 < ways[i - 1])
                ways[i] = LIM;
            else
                ways[i] = ways[i - 1] * 2;
        }
    }

    int n;
    long long k;
    rd(n, k);
    if (k > ways[n]) {
        cout << -1 << "\n";
        return;
    }

    vector<long long> ans;
    ans.reserve((size_t) n);

    int cur = 1;
    while (cur <= n) {
        int remaining = n - cur + 1;
        int chosenLen = 1;
        for (int len = 1; len <= remaining; ++len) {
            int rest = n - (cur + len - 1);
            long long cnt = ways[rest];
            if (k > cnt)
                k -= cnt;
            else {
                chosenLen = len;
                break;
            }
        }
        for (long long x = cur + chosenLen - 1; x >= cur; --x)
            ans.push_back(x);
        cur += chosenLen;
    }

    prt_vec(ans);
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
