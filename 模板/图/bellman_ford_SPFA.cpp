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

// 负环
void solve1() {
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> g(n + 1, vector<pii>());

    For(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        if (w >= 0) {
            g[v].emplace_back(u, w);
        }
    }

    auto spfa = [&]() -> bool {
        queue<int> q;
        vector<int> cnt(n + 1), dis(n + 1, inf), vis(n + 1);

        // 从点1开始（单源负环检测）
        dis[1] = 0;
        q.push(1);
        vis[1] = true;
        cnt[1] = 1;

        // 或者如果要检测整个图的负环（多源）：
        // for (int i = 1; i <= n; i++) {
        //     dis[i] = 0;
        //     q.push(i);
        //     vis[i] = true;
        //     cnt[i] = 1;
        // }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;

            for (auto &[v, w]: g[u]) {
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;

                    if (!vis[v]) {
                        cnt[v]++; // 入队次数+1
                        if (cnt[v] >= n) {
                            return true; // 检测到负环
                        }
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return false;
    };

    cout << (spfa() ? "YES" : "NO") << '\n';
}

// 最短路 + 负环 + 回溯路径
void solve2() {
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> g(n + 1, vector<pii>());

    For(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        if (w >= 0) {
            g[v].emplace_back(u, w);
        }
    }

    vector<int> dis(n + 1, inf);
    vector<int> pre(n + 1, -1);
    vector<bool> vis(n + 1, false);
    vector<int> cnt(n + 1, 0);

    auto spfa = [&]() -> bool {
        queue<int> q;
        dis[1] = 0;
        q.push(1);
        vis[1] = true;
        cnt[1] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;

            for (auto &[v, w]: g[u]) {
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    pre[v] = u;

                    if (!vis[v]) {
                        cnt[v]++;
                        if (cnt[v] >= n)
                            return false;
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return true;
    };

    if (!spfa()) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';

        if (dis[n] == inf) {
            cout << "不可达" << '\n';
        } else {
            vector<int> path;
            for (int cur = n; cur != -1; cur = pre[cur]) {
                path.push_back(cur);
            }
            reverse(path.begin(), path.end());

            cout << "最短距离: " << dis[n] << '\n';
            cout << "路径: ";
            for (int i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i < path.size() - 1)
                    cout << " -> ";
            }
            cout << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve1();
    return 0;
}
