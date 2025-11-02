#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
struct ZXS {
    int lc, rc, sum, size;
} a[10000000];
int nodecnt, root[10000000], n, m, w[233][233], q, ww[600000], f1[233][233][1050], f2[233][233][1050];
int getin() {
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = x * 10 + ch - 48, ch = getchar();
    return x;
}
int wt[30];
void putout(int x) {
    if (!x) {
        putchar('0');
        return;
    }
    int l = 0;
    while (x)
        wt[++l] = x % 10, x /= 10;
    while (l)
        putchar(wt[l--] + 48);
}
void build(int &rot, int lt, int rt) {
    rot = ++nodecnt;
    if (lt == rt)
        return;
    int mid = (lt + rt) >> 1;
    build(a[rot].lc, lt, mid), build(a[rot].rc, mid + 1, rt);
}
int update(int rot, int lt, int rt, int w) {
    int o = ++nodecnt;
    a[o] = a[rot], a[o].size = a[rot].size + 1, a[o].sum = a[rot].sum + w;
    if (lt == rt)
        return o;
    int mid = (lt + rt) >> 1;
    if (w <= mid)
        a[o].lc = update(a[o].lc, lt, mid, w);
    else
        a[o].rc = update(a[o].rc, mid + 1, rt, w);
    return o;
}
int query(int lt, int rt, int lq, int rq, int w) {
    if (lt == rt)
        return (w + lt - 1) / lt;
    int mid = (lt + rt) >> 1, t = a[a[rq].rc].sum - a[a[lq].rc].sum;
    if (w <= t)
        return query(mid + 1, rt, a[lq].rc, a[rq].rc, w);
    else
        return a[a[rq].rc].size - a[a[lq].rc].size + query(lt, mid, a[lq].lc, a[rq].lc, w - t);
}
void work1() {
    int maxw = -1e9 - 7;
    for (int i = 1; i <= m; i++)
        ww[i] = getin(), maxw = max(ww[i], maxw);
    build(root[0], 1, m);
    for (int i = 1; i <= m; i++)
        root[i] = update(root[i - 1], 1, maxw, ww[i]);
    for (int i = 1; i <= q; i++) {
        int y1, y2, h;
        y1 = getin(), y1 = root[getin() - 1], y2 = getin(), y2 = root[getin()], h = getin();
        if (a[y2].sum - a[y1].sum < h) {
            puts("Poor QLW");
            continue;
        }
        putout(query(1, maxw, y1, y2, h)), putchar(10);
    }
}
int getsum(int x1, int y1, int x2, int y2, int k, int f) {
    if (f == 1)
        return f1[x2][y2][k] - f1[x2][y1 - 1][k] - f1[x1 - 1][y2][k] + f1[x1 - 1][y1 - 1][k];
    else
        return f2[x2][y2][k] - f2[x2][y1 - 1][k] - f2[x1 - 1][y2][k] + f2[x1 - 1][y1 - 1][k];
}
void work2() {
    int maxw = -1e9 - 7;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            w[i][j] = getin(), maxw = max(maxw, w[i][j]);
    for (int k = 1; k <= maxw; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                f1[i][j][k] = f1[i - 1][j][k] + f1[i][j - 1][k] - f1[i - 1][j - 1][k] + (w[i][j] >= k) * w[i][j];
                f2[i][j][k] = f2[i - 1][j][k] + f2[i][j - 1][k] - f2[i - 1][j - 1][k] + (w[i][j] >= k);
            }
    for (int i = 1; i <= q; i++) {
        int x1 = getin(), y1 = getin(), x2 = getin(), y2 = getin(), h = getin();
        if (getsum(x1, y1, x2, y2, 1, 1) < h) {
            puts("Poor QLW");
            continue;
        }
        int l = 1, r = maxw, mid;
        while (l < r) {
            mid = (l + r + 1) >> 1;
            if (getsum(x1, y1, x2, y2, mid, 1) >= h)
                l = mid;
            else
                r = mid - 1;
        }
        putout(getsum(x1, y1, x2, y2, l, 2) - (getsum(x1, y1, x2, y2, l, 1) - h) / l), putchar(10);
    }
}
int main() {
    n = getin(), m = getin(), q = getin();
    if (n == 1)
        work1();
    else
        work2();
}
