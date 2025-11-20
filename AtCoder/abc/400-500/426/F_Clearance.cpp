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
constexpr int MOD2 = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

constexpr int N = 6e5 + 10;

#define ls id << 1
#define rs id << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define int long long
struct node {
    ll cnt, mi, tag;
} seg[N * 2];
int a[N];
node operator+(const node &l, const node &r) {
    node t = {0, 0, 0};
    t.cnt = l.cnt + r.cnt;
    t.mi = min(l.mi, r.mi);
    return t;
}
void build(int id, int l, int r) {
    seg[id].cnt = r - l + 1;
    if (l == r) {
        seg[id].mi = a[l];
        seg[id].cnt = 0;
        return;
    }
    int mid = l + r >> 1;
    build(lson);
    build(rson);
    seg[id] = seg[ls] + seg[rs];
}
void pushdown(int id) {
    if (seg[id].tag == 0)
        return;
    seg[ls].mi += seg[id].tag;
    seg[rs].mi += seg[id].tag;
    seg[ls].tag += seg[id].tag;
    seg[rs].tag += seg[id].tag;
    seg[id].tag = 0;
}
ll modify(int id, int l, int r, int ql, int qr, int x) {
    if (ql > qr)
        return 0;
    int ans = 0;
    if (ql <= l && qr >= r && seg[id].mi > x) {
        seg[id].mi -= x;
        seg[id].tag -= x;
        return x * (r - l + 1 - seg[id].cnt);
    }
    if (l == r) {
        ans = seg[id].mi;
        seg[id].mi = 1e18;
        seg[id].cnt = 1;
        return ans;
    }
    pushdown(id);
    int mid = l + r >> 1;
    if (ql <= mid)
        ans += modify(lson, ql, qr, x);
    if (qr > mid)
        ans += modify(rson, ql, qr, x);
    seg[id] = seg[ls] + seg[rs];
    return ans;
}

signed main() {
    int n, q;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build(1, 1, n);
    cin >> q;
    while (q--) {
        ll l, r, k;
        cin >> l >> r >> k;
        cout << modify(1, 1, n, l, r, k) << endl;
    }
    return 0;
}
