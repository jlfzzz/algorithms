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

template<typename T>
void read(T &x) {
    cin >> x;
}

template<typename T, typename... Args>
void read(T &x, Args &...args) {
    cin >> x;
    read(args...);
}

template<typename T>
void read(vector<T> &v) {
    for (auto &x: v)
        cin >> x;
}

int Multitest = 1;
vector<vector<vector<long long>>> memo;
int n;
long long dfs(int i, int j, int dir) {
    if (j == 0)
        return 0;
    if (i < 1 || i > n)
        return 1;

    int idx = (dir == 1 ? 1 : 0);
    if (memo[i][j][idx] != -1)
        return memo[i][j][idx];

    long long res = (dfs(i + dir, j, dir) + dfs(i - dir, j - 1, -dir)) % MOD;
    return memo[i][j][idx] = res;
}

void solve() {
    int k;
    cin >> n >> k;

    memo.assign(n + 2, vector<vector<long long>>(k + 1, vector<long long>(2, -1)));

    long long ans = dfs(1, k, 1);
    prt(ans);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    if (Multitest) {
        cin >> T;
    }
    while (T--)
        solve();
    return 0;
}
