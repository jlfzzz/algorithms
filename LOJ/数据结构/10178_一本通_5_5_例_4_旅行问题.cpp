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

int Multitest = 0;

void init() {}

void solve() {
    int n;
    cin >> n;

    vector<int> P(n + 1), D(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> P[i] >> D[i];
    }

    auto f = [&](const vector<int> &diff) -> vector<char> {
        int N = n;
        vector<int> pre(2 * N + 1);
        for (int t = 1; t <= 2 * N; t++) {
            int idx = (t - 1) % N + 1;
            pre[t] = pre[t - 1] + diff[idx];
        }
        multiset<int> window;
        for (int j = 1; j <= N; j++)
            window.insert(pre[j]);
        vector<char> ok(N + 1);
        for (int i = 1; i <= N; i++) {
            int base = pre[i - 1];
            int mn = *window.begin();
            if (mn - base >= 0)
                ok[i] = 1;
            auto it = window.find(pre[i]);
            if (it != window.end())
                window.erase(it);
            window.insert(pre[i + N]);
        }
        return ok;
    };

    // 顺时针
    vector<int> cw_diff(n + 1);
    for (int i = 1; i <= n; i++)
        cw_diff[i] = P[i] - D[i];
    vector<char> ans(n + 1, 0);
    auto cw_ok = f(cw_diff);
    for (int i = 1; i <= n; i++)
        if (cw_ok[i])
            ans[i] = 1;

    // 逆时针，构造反序序列 R[k] = n-k+1，rev_diff[k] = P[R[k]] - D[R[k+1]] (R[n+1]=R[1]=n)
    vector<int> rev_diff(n + 1);
    for (int k = 1; k <= n; k++) {
        int Rk = n - k + 1;
        int Rk1 = (k == n ? n : n - k);
        rev_diff[k] = P[Rk] - D[Rk1];
    }
    auto ccw_ok = f(rev_diff);
    for (int k = 1; k <= n; k++) {
        int station = n - k + 1; // R[k]
        if (ccw_ok[k])
            ans[station] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (ans[i]) {
            prt("TAK");
        } else {
            prt("NIE");
        }
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
