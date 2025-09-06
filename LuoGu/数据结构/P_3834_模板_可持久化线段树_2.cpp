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
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}


class PST {
public:
    int n;
    int idx;
    vector<int> root, lc, rc, sum;

    explicit PST(int n) : n(n), idx(0), root(n + 1), lc(22 * n + 5), rc(22 * n + 5), sum(22 * n + 5) {}

    int update(int pre, int L, int R, int p) {
        int cur = ++idx;
        newnode(pre, cur);
        sum[cur] = sum[pre] + 1;
        if (L == R)
            return cur;
        int mid = (L + R) >> 1;
        if (p <= mid)
            lc[cur] = update(lc[cur], L, mid, p);
        else
            rc[cur] = update(rc[cur], mid + 1, R, p);
        return cur;
    }

    int getkth(int pre, int cur, int L, int R, int k) {
        if (L == R)
            return L;
        int left_cnt = sum[lc[cur]] - sum[lc[pre]];
        int mid = (L + R) >> 1;
        if (k <= left_cnt)
            return getkth(lc[pre], lc[cur], L, mid, k);
        return getkth(rc[pre], rc[cur], mid + 1, R, k - left_cnt);
    }

    void newnode(int pre, int cur) {
        lc[cur] = lc[pre];
        rc[cur] = rc[pre];
        sum[cur] = sum[pre];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    vector<int> b;
    b.reserve(n);
    for (int i = 1; i <= n; i++)
        b.push_back(a[i]);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int tot = (int) b.size();

    PST pst(n);
    vector<int> rev(tot + 1);
    for (int i = 1; i <= tot; i++)
        rev[i] = b[i - 1];

    pst.root[0] = 0;
    for (int i = 1; i <= n; i++) {
        int p = int(lower_bound(b.begin(), b.end(), a[i]) - b.begin()) + 1;
        pst.root[i] = pst.update(pst.root[i - 1], 1, tot, p);
    }

    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        int id = pst.getkth(pst.root[l - 1], pst.root[r], 1, tot, k);
        cout << rev[id] << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}
