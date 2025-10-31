#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
int head[501], nxt[1001], point[1001], weight[1001], sum[501], stack[1001], deep[1001];
long long f[111][111][51], g[111][111][51];
int n, tot, K, vi, di, stackSize;
void addedge(int x, int y, int cap) {
    tot++;
    nxt[tot] = head[x];
    head[x] = tot;
    point[tot] = y;
    weight[tot] = cap;
}
void dfs(int i) {
    stack[++stackSize] = i;
    for (int tmp = head[i]; tmp; tmp = nxt[tmp]) {
        int v = point[tmp];
        deep[v] = deep[i] + weight[tmp];
        dfs(v);
        for (int j = 1; j <= stackSize; j++)
            for (int k = K; k >= 0; k--) {
                f[i][stack[j]][k] += f[v][stack[j]][0];
                g[i][stack[j]][k] += f[v][i][0];
                for (int x = 0; x <= k; x++) {
                    f[i][stack[j]][k] = min(f[i][stack[j]][k], f[i][stack[j]][k - x] + f[v][stack[j]][x]);
                    g[i][stack[j]][k] = min(g[i][stack[j]][k], g[i][stack[j]][k - x] + f[v][i][x]);
                }
            }
    }
    // 这里是将f和g合并了，因为之后就不在乎i有没有建伐木场，只关心i和i的子树建了多少。
    for (int j = 1; j <= stackSize; j++)
        for (int k = 0; k <= K; k++) {
            if (k >= 1)
                f[i][stack[j]][k] = min(f[i][stack[j]][k] + sum[i] * (deep[i] - deep[stack[j]]), g[i][stack[j]][k - 1]);
            // 这里是g[i][stack[j]][k-1]的原因是：因为我们之前算g的时候，是假设i上有伐木场。而我们实际上没有把这个伐木场的数量加进去。所以合并前g[i][j][k]实际上代表的是g[i][j][k+1]
            else
                f[i][stack[j]][k] += sum[i] * (deep[i] - deep[stack[j]]);
        }

    stackSize--;
}
int main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &sum[i], &vi, &di);
        addedge(vi, i, di);
    }
    dfs(0);
    printf("%d\n", f[0][0][K]);
}
