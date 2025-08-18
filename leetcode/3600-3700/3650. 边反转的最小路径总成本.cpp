
class Solution {
public:
    int minCost(int n, vector<vector<int>> &edges) {
        vector<vector<pair<int, int>>> g(n);
        vector<vector<pair<int, int>>> fa(n);
        for (auto &e: edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v, w);
            fa[v].emplace_back(u, w);
        }

        vector<int> dis(n, INT_MAX);
        dis[0] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, 0);

        while (!pq.empty()) {
            auto [d, x] = pq.top();
            pq.pop();

            if (x == n - 1)
                return d;

            if (d > dis[x])
                continue;

            for (auto [v, w]: g[x]) {
                int newDist = d + w;
                if (newDist < dis[v]) {
                    dis[v] = newDist;
                    pq.emplace(newDist, v);
                }
            }

            for (auto [u, w]: fa[x]) {
                int newDist = d + 2 * w;
                if (newDist < dis[u]) {
                    dis[u] = newDist;
                    pq.emplace(newDist, u);
                }
            }
        }
        return -1;
    }
};
