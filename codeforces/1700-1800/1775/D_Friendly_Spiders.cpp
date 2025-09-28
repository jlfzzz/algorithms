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

int Multitest = 0;

void init() {}

void solve() {
    int n;
    read(n);

    int m = 0;
    vector<int> a(n);
    read_vec(a);
    m = ranges::max(a);

    vector<int> minp(m + 1), primes;
    for (int i = 2; i <= m; i++) {
        if (!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for (auto p: primes) {
            if (i * p > m)
                break;
            minp[i * p] = p;
            if (p == minp[i])
                break;
        }
    }

    int s, t;
    read(s, t);
    s--, t--;

    vector<vector<int>> f(m + 1);
    for (int i = 0; i < n; i++) {
        for (int x = a[i]; x > 1; x /= minp[x]) {
            f[minp[x]].push_back(i);
        }
    }

    vector<int> dis(n + m + 1, -1), prev(n + m + 1);

    queue<tuple<int, int, int>> q;
    q.emplace(s, 0, -1);

    while (!q.empty()) {
        auto [u, d, p] = q.front();
        q.pop();

        if (dis[u] != -1)
            continue;

        dis[u] = d;
        prev[u] = p;

        if (u < n) {
            for (int x = a[u]; x > 1; x /= minp[x]) {
                q.emplace(n + minp[x], d + 1, u);
            }
        } else {
            for (auto x: f[u - n]) {
                q.emplace(x, d + 1, u);
            }
        }
    }

    if (dis[t] == -1) {
        prt(-1);
        return;
    }

    vector<int> ans;
    for (int i = t; i != -1; i = prev[i]) {
        if (i < n)
            ans.push_back(i);
    }

    reverse(ans.begin(), ans.end());
    prt(ans.size());
    for (int &x: ans)
        x++;
    prt_vec(ans);
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
}
