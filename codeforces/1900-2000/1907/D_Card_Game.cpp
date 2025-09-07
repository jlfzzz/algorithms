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

void init() {}

void solve() {
    int n;
    cin >> n;

    char trump;
    cin >> trump;

    auto sid = [&](char c) {
        if (c == 'C')
            return 0;
        if (c == 'D')
            return 1;
        if (c == 'H')
            return 2;
        return 3;
    };

    vector<vector<string>> g(4);
    For(i, 2 * n) {
        string s;
        cin >> s;
        g[sid(s[1])].push_back(s);
    }

    auto cmp = [&](const string &a, const string &b) { return a[0] < b[0]; };
    vector<pair<string, string>> ans;
    vector<string> rest;

    int tid = sid(trump);
    for (int i = 0; i < 4; i++)
        if (i != tid) {
            sort(g[i].begin(), g[i].end(), cmp);
            int m = g[i].size();
            for (int j = 0; j + 1 < m; j += 2)
                ans.push_back({g[i][j], g[i][j + 1]});
            if (m % 2 == 1)
                rest.push_back(g[i].back());
        }

    sort(g[tid].begin(), g[tid].end(), cmp);
    if (g[tid].size() < rest.size()) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    for (int i = 0; i < rest.size(); i++)
        ans.push_back({rest[i], g[tid][i]});
    vector<string> rem;
    for (int i = rest.size(); i < g[tid].size(); i++)
        rem.push_back(g[tid][i]);
    if (rem.size() % 2 == 1) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (int i = 0; i < rem.size(); i += 2)
        ans.push_back({rem[i], rem[i + 1]});

    for (auto &p: ans)
        cout << p.first << ' ' << p.second << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
