#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> f(n, -1);

    std::vector<std::array<int, 3>> ans;

    auto add = [&](this auto &&self, int u, int v) -> void {
        if (f[u] == v) {
            f[u] = -1;
            f[v] = -1;
            return;
        }
        if (f[u] != -1) {
            int w = f[u];
            ans.push_back({u, v, w});
            f[u] = -1;
            f[w] = -1;
            self(v, w);
            return;
        }
        if (f[v] != -1) {
            int w = f[v];
            ans.push_back({u, v, w});
            f[v] = -1;
            f[w] = -1;
            self(u, w);
            return;
        }
        f[u] = v;
        f[v] = u;
    };

    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        add(u, v);
    }

    std::vector<std::array<int, 2>> p;
    for (int i = 0; i < n; i++) {
        if (f[i] > i) {
            p.push_back({i, f[i]});
        }
    }

    if (!p.empty()) {
        auto [a, b] = p[0];
        for (int i = 1; i < p.size(); i++) {
            auto [u, v] = p[i];
            ans.push_back({a, u, v});
        }
        for (int i = 0; i < n; i++) {
            if (f[i] != -1) {
                continue;
            }
            ans.push_back({a, b, i});
            b = i;
        }
    }

    std::cout << ans.size() << "\n";
    for (auto [u, v, w]: ans) {
        std::cout << u + 1 << " " << v + 1 << " " << w + 1 << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
