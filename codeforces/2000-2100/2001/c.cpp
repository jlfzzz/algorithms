#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n, ans;
    vector<pair<int, int>> edges;

    cin >> n;

    // 核心思想：从节点1出发，找到连接到每个其他节点的路径上的第一条边
    for (int i = 2; i <= n; i++) {
        cout << "? " << 1 << " " << i << endl;
        cin >> ans;

        int u = 1, v = i;
        // 如果 ans 不是端点，说明路径上有中间节点
        while (ans != u && ans != v) {
            u = ans; // 更新 u 为中间节点
            cout << "? " << u << " " << v << endl;
            cin >> ans;
        }
        // 现在 ans 是端点之一，说明找到了一条边 (u, v)
        edges.emplace_back(u, v);
    }

    cout << "! ";
    for (auto &edge: edges) {
        cout << edge.first << " " << edge.second << " ";
    }
    cout << endl;
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
