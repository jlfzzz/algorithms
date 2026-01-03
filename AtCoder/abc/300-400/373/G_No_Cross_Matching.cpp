#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define db long double
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;

const db INF_DB = 1e18;
const int MAXN = 305;

struct KM {
    int n;
    db w[MAXN][MAXN]; // 边权
    db lx[MAXN], ly[MAXN]; // 顶标
    int match[MAXN]; // match[j] = i: 右边第j个点匹配左边第i个点
    db slack[MAXN];
    int way[MAXN];
    int pre[MAXN];
    bool vis[MAXN];

    KM(int _n) : n(_n) {
        // 初始化边权为 -INF
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                w[i][j] = -INF_DB;
    }

    void add_edge(int u, int v, db val) { w[u][v] = val; }

    void solve() {
        // 初始化顶标
        for (int i = 1; i <= n; ++i) {
            match[i] = 0;
            lx[i] = -INF_DB;
            ly[i] = 0;
            for (int j = 1; j <= n; ++j) {
                lx[i] = max(lx[i], w[i][j]);
            }
        }

        // 逐个匹配左边的点 i
        for (int i = 1; i <= n; ++i) {
            fill(slack + 1, slack + 1 + n, INF_DB);
            fill(vis + 1, vis + 1 + n, false);
            int j_cur = 0;
            match[0] = i; // 0号点作为辅助点，暂存当前正在匹配的左点

            do {
                vis[j_cur] = true;
                int i_next = match[j_cur];
                db delta = INF_DB;
                int j_next = 0;

                for (int j = 1; j <= n; ++j) {
                    if (!vis[j]) {
                        db val = lx[i_next] + ly[j] - w[i_next][j];
                        if (val < slack[j]) {
                            slack[j] = val;
                            pre[j] = j_cur;
                        }
                        if (slack[j] < delta) {
                            delta = slack[j];
                            j_next = j;
                        }
                    }
                }

                for (int j = 0; j <= n; ++j) {
                    if (vis[j]) {
                        lx[match[j]] -= delta;
                        ly[j] += delta;
                    } else {
                        slack[j] -= delta;
                    }
                }
                j_cur = j_next;
            } while (match[j_cur] != 0);

            // 倒推更新增广路
            do {
                int j_pre = pre[j_cur];
                match[j_cur] = match[j_pre];
                j_cur = j_pre;
            } while (j_cur);
        }
    }
};

// ---------------- 主程序 ----------------

void solve() {
    int n;
    cin >> n;
    vector<pair<ll, ll>> p(n), q(n);
    for (auto &x: p)
        cin >> x.first >> x.second;
    for (auto &x: q)
        cin >> x.first >> x.second;

    KM km(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            db dist = hypot((db) p[i].first - q[j].first, (db) p[i].second - q[j].second);
            km.add_edge(i + 1, j + 1, -dist);
        }
    }

    km.solve();

    vector<int> ans(n + 1);
    for (int j = 1; j <= n; j++) {
        ans[km.match[j]] = j;
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
