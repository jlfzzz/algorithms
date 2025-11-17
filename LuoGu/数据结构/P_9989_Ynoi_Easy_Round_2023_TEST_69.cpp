#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t;

const int MAXN = 200000 + 5;
const ll LIM = (ll) 1e18;
const ull MOD = 1ull << 32;

struct Node {
    int l, r;
    ull sum;
    i128 lcm;
    bool big;
} seg[MAXN * 4];

i128 my_gcd(i128 a, i128 b) {
    while (b != 0) {
        i128 t = a % b;
        a = b;
        b = t;
    }
    return a;
}

i128 safe_lcm(i128 a, i128 b, bool &big) {
    if (a == 0 || b == 0)
        return 0;
    i128 g = my_gcd(a, b);
    a /= g;
    if (a > (i128) LIM / b) {
        big = true;
        return (i128) LIM + 1;
    }
    i128 res = a * b;
    if (res > (i128) LIM) {
        big = true;
        return (i128) LIM + 1;
    }
    return res;
}

void push_up(int u) {
    int ls = u << 1, rs = u << 1 | 1;
    seg[u].sum = (seg[ls].sum + seg[rs].sum) & (MOD - 1); 

    bool big_here = false;
    i128 l = safe_lcm(seg[ls].lcm, seg[rs].lcm, big_here);

    seg[u].big = seg[ls].big || seg[rs].big || big_here;
    seg[u].lcm = l;
}

void build(int u, int l, int r, const vector<ll> &a) {
    seg[u].l = l;
    seg[u].r = r;
    if (l == r) {
        i128 v = (i128) a[l];
        seg[u].sum = (ull) v & (MOD - 1);
        seg[u].lcm = v;
        seg[u].big = false;
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid, a);
    build(u << 1 | 1, mid + 1, r, a);
    push_up(u);
}

void update(int u, int L, int R, i128 x) {
    int l = seg[u].l, r = seg[u].r;
    if (r < L || l > R)
        return;

    if (!seg[u].big) {
        i128 lcm_here = seg[u].lcm;
        if (lcm_here != 0 && x % lcm_here == 0) {
            return;
        }
    }

    if (l == r) {
        i128 v = seg[u].lcm;
        i128 g = my_gcd(v, x);
        seg[u].lcm = g;
        seg[u].sum = (ull) g & (MOD - 1);
        seg[u].big = false;
        return;
    }

    update(u << 1, L, R, x);
    update(u << 1 | 1, L, R, x);
    push_up(u);
}

ull query(int u, int L, int R) {
    int l = seg[u].l, r = seg[u].r;
    if (r < L || l > R)
        return 0;
    if (L <= l && r <= R)
        return seg[u].sum;
    ull left = query(u << 1, L, R);
    ull right = query(u << 1 | 1, L, R);
    return (left + right) & (MOD - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    build(1, 1, n, a);

    for (int i = 0; i < m; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            if (l > r)
                swap(l, r);
            update(1, l, r, (i128) x);
        } else if (type == 2) {
            int l, r;
            cin >> l >> r;
            if (l > r)
                swap(l, r);
            ull ans = query(1, l, r);
            cout << (ans & (MOD - 1)) << '\n';
        }
    }

    return 0;
}
