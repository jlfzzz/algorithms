#include <bits/stdc++.h>
using namespace std;



const int INF = 1e9; // 无穷大
const int N = 510;   // 最大点数

int dist[N][N];      // dist[i][j] 表示 i 到 j 的最短距离


// 必须是kij。k是中间节点，i,j是左右两个。必须这样顺序确保i->k,k->j所以i->j
void floyd(int n) {
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main() {
    int n, m;
    cin >> n >> m; // n 个点，m 条边
    // 初始化
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dist[i][j] = (i == j ? 0 : INF);

    // 读入边
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w); // 防止重边
    }

    // 运行 Floyd
    floyd(n);

    // 输出结果
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
