#include <bits/stdc++.h>
#include <type_traits>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<pii> edges(n);
    vector<int> deg(n + 1);
    vector<vector<int>> graph(n + 1, vector<int>());
    For(i, n - 1) {
        int x, y;
        cin >> x >> y;
        edges[i] = {x, y};
        deg[x]++;
        deg[y]++;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    if (n == 2) {
        cout << "NO\n";
        return;
    }
    int root = -1;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 2) {
            root = i;
        }
    }
    if (root == -1) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";

    vector<pii> ans;
    auto dfs = [&](this auto &&dfs, int i, int fa, bool in) -> void {
        for (int v: graph[i]) {
            if (v == fa)
                continue;

            if (in) {
                ans.emplace_back(v, i);
                // cout << v << ' ' << i << '\n';
                dfs(v, i, !in);
            } else {
                // cout << i << ' ' << v << '\n';
                ans.emplace_back(i, v);
                dfs(v, i, !in);
            }
        }
    };
    bool f = false;
    for (int v: graph[root]) {
        dfs(v, root, f);

        if (!f) {
            ans.emplace_back(v, root);
        } else {
            ans.emplace_back(root, v);
        }
        f = !f;
    }

    for (auto &[a, b]: ans) {
        cout << a << ' ' << b << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
