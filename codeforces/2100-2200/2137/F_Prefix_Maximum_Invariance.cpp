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
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];

    struct BIT {
        int N;
        vector<int> t;
        void init(int n) {
            N = n;
            t.assign(N + 2, 0);
        }
        void update(int idx, int val) {
            for (; idx <= N; idx += idx & -idx)
                t[idx] = max(t[idx], val);
        }
        int query(int idx) {
            int res = 0;
            for (; idx > 0; idx -= idx & -idx)
                res = max(res, t[idx]);
            return res;
        }
    } bit;

    bit.init(2 * n + 1);

    vector<int> prev(n + 1, 0);
    vector<int> st;
    st.reserve(n);

    for (int i = 1; i <= n; i++) {
        while (!st.empty() && a[st.back()] < a[i])
            st.pop_back();
        prev[i] = st.empty() ? 0 : st.back();
        st.push_back(i);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int idx_a = (2 * n + 1 - a[i] + 1);
        bit.update(idx_a, i);

        int right = 2 * n + 1 - b[i] + 1;
        int pos = bit.query(right);

        int pre = prev[i];
        int t1 = min(pre, pos);
        int t2 = (b[i] == a[i]) ? (i - pre) : 0;
        int total = t1 + t2;
        ans += total * (n - i + 1);
    }

    cout << ans << '\n';
}

void solve2() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];

    int MAXV = 2 * n; // 值域上界

    struct SegTree {
        int N;
        vector<long long> tree;
        void init(int n) {
            N = n;
            tree.assign(4 * (N + 5), 0);
        }
        void add(int idx, long long delta, int p, int l, int r) {
            if (l == r) {
                tree[p] += delta;
                return;
            }
            int mid = (l + r) >> 1;
            if (idx <= mid)
                add(idx, delta, p << 1, l, mid);
            else
                add(idx, delta, p << 1 | 1, mid + 1, r);
            tree[p] = tree[p << 1] + tree[p << 1 | 1];
        }
        void add(int idx, long long delta) {
            if (idx < 1)
                return;
            if (idx > N)
                return;
            add(idx, delta, 1, 1, N);
        }
        long long query(int L, int R, int p, int l, int r) {
            if (L > R)
                return 0;
            if (L <= l && r <= R)
                return tree[p];
            int mid = (l + r) >> 1;
            long long res = 0;
            if (L <= mid)
                res += query(L, R, p << 1, l, mid);
            if (R > mid)
                res += query(L, R, p << 1 | 1, mid + 1, r);
            return res;
        }
        long long query(int L, int R) {
            if (L < 1)
                L = 1;
            if (R > N)
                R = N;
            if (L > R)
                return 0;
            return query(L, R, 1, 1, N);
        }
    } seg;

    seg.init(MAXV);

    vector<int> pre(n + 1, 0);
    vector<int> stk;
    stk.reserve(n);

    long long ans = 0;
    for (int r = 1; r <= n; ++r) {
        while (!stk.empty() && a[stk.back()] < a[r]) {
            int p = stk.back();
            stk.pop_back();
            long long wp = p - pre[p];
            seg.add((int) a[p], -wp);
        }
        pre[r] = stk.empty() ? 0 : stk.back();

        long long t1 = seg.query((int) b[r], MAXV); // 非首次最大：累计所有活跃 p 且 a[p]≥b[r] 的权重
        long long t2 = (b[r] == a[r]) ? (r - pre[r]) : 0; // 首次最大：r 自身等于时的权重

        long long Cr = t1 + t2;
        ans += Cr * (n - r + 1);

        long long wr = r - pre[r];
        seg.add((int) a[r], wr);
        stk.push_back(r);
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve2();
    return 0;
}
