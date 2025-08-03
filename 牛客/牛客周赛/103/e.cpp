#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

int n;
vector<int> weights;
vector<vector<int>> adj;
vector<vector<int>> children;
vector<int> parent;
unordered_set<ll> all_values;
const int MAX_LEN = 21;

void build(int u, int p) {
    parent[u] = p;
    for (int v: adj[u]) {
        if (v != p) {
            children[u].push_back(v);
            build(v, u);
        }
    }
}

void solve() {
    int q;
    cin >> n >> q;
    string s;
    cin >> s;

    weights.resize(n + 1);
    for (int i = 0; i < n; ++i) {
        weights[i + 1] = s[i] - '0';
    }

    adj.assign(n + 1, vector<int>());
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    parent.resize(n + 1);
    children.assign(n + 1, vector<int>());
    build(1, 0);

    for (int i = 1; i <= n; ++i) {
        auto dfs = [&](this auto &&dfs, int u, ll current, int len) {
            all_values.insert(current);

            if (len >= MAX_LEN) {
                return;
            }

            for (int v: children[u]) {
                ll next = current * 2 + weights[v];
                dfs(v, next, len + 1);
            }
        };
        dfs(i, weights[i], 1);

        ll up = weights[i];
        int len = 1;
        int current = i;
        while (parent[current] != 0) {
            current = parent[current];
            len++;
            if (len > MAX_LEN) {
                break;
            }
            up = up * 2 + weights[current];
            all_values.insert(up);
        }
    }

    for (int k = 0; k < q; ++k) {
        ll x;
        cin >> x;
        if (all_values.count(x)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
