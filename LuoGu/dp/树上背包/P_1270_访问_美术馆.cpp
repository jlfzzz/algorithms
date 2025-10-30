#include <cstdio>
#include <iostream>

using namespace std;

const int maxn = 1e4 + 10;

int tim, num, tot;
int hav[maxn], g[maxn], dp[maxn][610];
struct line {
    int to, next, w;
} edge[maxn * 2];

void add1(int a, int b, int c) {
    edge[++tot].to = b;
    edge[tot].w = c;
    edge[tot].next = g[a];
    g[a] = tot;
}
void dfs(int cur, int fa)
{
    int w = 0, x = 0;
    scanf("%d %d", &w, &x);
    add1(fa, cur, w * 2);
    if (x) {
        hav[cur] = x;
        return;
    }
    dfs(++num, cur);
    dfs(++num, cur);
}
void dfs2(int cur) {
    if (hav[cur])
    {
        for (int i = 5; i <= tim; i++)
            dp[cur][i] = min(hav[cur], dp[cur][i - 5] + 1);
        return;
    }
    for (int i = g[cur]; i; i = edge[i].next)       
    {
        dfs2(edge[i].to);
        for (int j = tim; j >= edge[i].w; j--)
            for (int k = edge[i].w; k <= j; k++)
                dp[cur][j] = max(dp[cur][j], dp[cur][j - k] + dp[edge[i].to][k - edge[i].w]);
    }
}
void print(int cur) {
    cout << cur << " ";
    for (int i = g[cur]; i; i = edge[i].next)
        print(edge[i].to);
}
int main() {
    scanf("%d", &tim);
    dfs(++num, 0);
    dfs2(0);
    cout << dp[0][tim - 1];
    return 0;
}
