#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 11;

struct edge {
    int t, w;
    edge(int t, int w) : t(t), w(w) {}
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> b(n);
    for (auto &x: b) {
        cin >> x;
    }
    vector<vector<edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        int s, t, w;
        cin >> s >> t >> w;
        --s;
        --t;
        graph[s].push_back(edge(t, w));
    }
    auto check = [&](int maxW) {
        vector<int> best(n, 0);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && best[i] == 0) {
                continue;
            }
            best[i] += b[i];
            best[i] = min(best[i], maxW);
            for (auto p: graph[i]) {
                if (p.w <= best[i]) {
                    best[p.t] = max(best[p.t], best[i]);
                }
            }
        }
        return (best.back() > 0);
    };
    if (!check(INF)) {
        cout << -1 << endl;
        return;
    }
    int l = 0, r = INF;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
