#include <bits/stdc++.h>
using namespace std;
#define int long long
int read() {
    int f = 0, s = 0;
    char c = getchar();
    while (c > '9' || c < '0')
        f = (c == '-'), c = getchar();
    while (c >= '0' && c <= '9')
        s = (s << 3) + (s << 1) + (c ^ '0'), c = getchar();
    return f ? -s : s;
}

const int N = 100005;
const int M = 105;
int n, V;
int a[N];
int t1, t2;

const int E = 200005;
int to[E], nx[E], h[N], tot = 0;
inline void add(int a, int b) {
    to[++tot] = b;
    nx[tot] = h[a];
    h[a] = tot;
}
inline void link(int a, int b) {
    add(a, b);
    add(b, a);
}
int f[N][M][2];
int ans = 0;

const long long inf = 1e18;
int w[N];
void dfs1(int u, int fa) {
    w[u] = 0;
    for (int i = h[u]; i; i = nx[i])
        if (to[i] != fa && to[i])
            dfs1(to[i], u), w[u] += a[to[i]];
    for (int i = 0; i <= V; i++)
        for (int j = 0; j < 2; j++)
            f[u][i][j] = -inf;
    f[u][0][0] = 0;
    f[u][1][1] = w[u];
    for (int i = h[u]; i; i = nx[i])
        if (to[i] != fa && to[i]) {
            for (int j = 0; j <= V; j++) {
                long long tmp = max(f[to[i]][j][0], f[to[i]][j][1]);
                f[u][j][0] = max((long long) f[u][j][0], tmp);
                f[u][j + 1][1] = max((long long) f[u][j + 1][1], tmp + w[u]);
            }
        }
}
long long t[N][M][2][2];
void dfs2(int u, int fa) {
    for (int i = 0; i <= V; i++)
        ans = max(ans, (int) max((long long) f[u][i][0], (long long) f[u][i][1]));
    for (int i = 0; i <= V; i++)
        for (int j = 0; j < 2; j++)
            t[u][i][j][0] = t[u][i][j][1] = -inf;
    for (int i = h[u]; i; i = nx[i]) {
        for (int j = 0; j <= V; j++)
            for (int k = 0; k < 2; k++) {
                if (f[to[i]][j][k] > t[u][j][k][0])
                    swap(t[u][j][k][1], t[u][j][k][0]), t[u][j][k][0] = f[to[i]][j][k];
                else if (f[to[i]][j][k] > t[u][j][k][1])
                    t[u][j][k][1] = f[to[i]][j][k];
            }
    }
    for (int i = h[u]; i; i = nx[i])
        if (to[i] != fa) {
            w[to[i]] += a[u];
            for (int j = V; j >= 0; j--) {
                long long g0 = -inf, g1 = -inf;
                if (f[to[i]][j][0] == t[u][j][0][0])
                    g0 = max(g0, t[u][j][0][1]);
                else
                    g0 = max(g0, t[u][j][0][0]);
                if (f[to[i]][j][1] == t[u][j][1][0])
                    g0 = max(g0, t[u][j][1][1]);
                else
                    g0 = max(g0, t[u][j][1][0]);
                if (j) {
                    if (f[to[i]][j - 1][0] == t[u][j - 1][0][0])
                        g1 = max(g1, t[u][j - 1][0][1] + w[u] - a[to[i]]);
                    else
                        g1 = max(g1, t[u][j - 1][0][0] + w[u] - a[to[i]]);
                    if (f[to[i]][j - 1][1] == t[u][j - 1][1][0])
                        g1 = max(g1, t[u][j - 1][1][1] + w[u] - a[to[i]]);
                    else
                        g1 = max(g1, t[u][j - 1][1][0] + w[u] - a[to[i]]);
                }
                if (j == 1)
                    g1 = max(g1, w[u] - a[to[i]]);
                f[u][j][0] = g0;
                f[u][j][1] = g1;
                long long tmp = max(g0, g1);
                f[to[i]][j][0] = max((long long) f[to[i]][j][0], tmp);
                f[to[i]][j][1] += a[u];
                if (j == 0)
                    f[to[i]][j][1] = -inf;
                f[to[i]][j + 1][1] = max((long long) f[to[i]][j + 1][1], tmp + w[to[i]]);
            }
            dfs2(to[i], u);
        }
}

signed main() {
    n = read();
    V = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    for (int i = 1; i < n; i++)
        t1 = read(), t2 = read(), link(t1, t2);
    dfs1(1, 0);
    dfs2(1, 0);
    printf("%lld", (long long) ans);
    return 0;
}
