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

int Multitest = 0;

void init() {}

void solve() {
    int n;
    rd(n);
    vector<int> a(n + 1);
    rd_vec(a, 1);

    const int MAX_A = 5000;
    const int MAX_X = 8192;

    vector<vector<int>> positions(MAX_A + 1);
    for (int i = 1; i <= n; i++) {
        positions[a[i]].push_back(i);
    }

    const int INF_POS = n + 5;
    vector<int> dp(MAX_X, INF_POS);
    dp[0] = 0; // 位置 0 表示尚未选择任何元素

    for (int val = 0; val <= MAX_A; val++) {
        if (positions[val].empty())
            continue;

        auto ndp = dp;
        const auto &pos = positions[val];

        for (int x = 0; x < MAX_X; x++) {
            int last_pos = dp[x];
            if (last_pos >= INF_POS)
                continue; // 不可达

            auto it = upper_bound(pos.begin(), pos.end(), last_pos);
            if (it == pos.end())
                continue; // 之后没有该值的出现位置

            int new_pos = *it;
            int nx = x ^ val;
            if (new_pos < ndp[nx])
                ndp[nx] = new_pos;
        }

        dp.swap(ndp);
    }

    vector<int> ans;
    for (int x = 0; x < MAX_X; x++) {
        if (dp[x] < INF_POS)
            ans.push_back(x);
    }

    prt(ans.size());
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
