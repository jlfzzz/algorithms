#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
using namespace std;
const int N = 2e5 + 5;
int n, m, p, lastans;
struct NODE {
    int l, r;
    int maxx, minn;
} tr[N << 2];
void build(int p, int l, int r) {
    tr[p].l = l;
    tr[p].r = r;
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
}
int dfs(int p, int mrs) {
    if (tr[p].l == tr[p].r) {
        return tr[p].l + max(tr[p].maxx, mrs);
    }
    if (tr[rs].maxx <= mrs) {
        int mid = (tr[p].l + tr[p].r) >> 1;
        return min(mid + 1 + mrs, dfs(ls, mrs));
    } else if (tr[rs].maxx > mrs) {
        return min(tr[p].minn, dfs(rs, mrs));
    }
}
void push_up(int p) {
    tr[p].maxx = max(tr[ls].maxx, tr[rs].maxx);
    tr[p].minn = dfs(ls, tr[rs].maxx);
}
void updata(int p, int x, int k) {
    if (tr[p].l == tr[p].r) {
        tr[p].maxx = k - x;
        tr[p].minn = k;
        return;
    }
    int mid = (tr[p].l + tr[p].r) >> 1;
    if (x <= mid)
        updata(ls, x, k);
    else
        updata(rs, x, k);
    push_up(p);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> p;
    build(1, 1, 2 * n);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        updata(1, i, x);
        updata(1, i + n, x);
    }
    lastans = tr[1].minn + n - 1;
    cout << lastans << '\n';
    while (m--) {
        int x, y;
        cin >> x >> y;
        if (p == 1) {
            x ^= lastans;
            y ^= lastans;
        }
        updata(1, x, y);
        updata(1, x + n, y);
        lastans = tr[1].minn + n - 1;
        cout << lastans << '\n';
    }
    cout << endl;
    return 0;
}
