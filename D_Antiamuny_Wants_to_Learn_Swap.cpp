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

// struct Node {
//     int val = 0;
// };

// class PST {
// private:
//     int n, ts;
//     std::vector<int> lc, rc;
//     std::vector<Node> tree;

//     void newnode(int pre, int cur) {
//         lc[cur] = lc[pre];
//         rc[cur] = rc[pre];
//         tree[cur] = tree[pre];
//     }

//     Node merge(const Node &left, const Node &right) { return Node{left.val + right.val}; }

//     int _build(const std::vector<int> &arr, int l, int r) {
//         int cur = ++ts;
//         if (l == r) {
//             tree[cur] = Node{arr[l]};
//             return cur;
//         }
//         int m = (l + r) / 2;
//         lc[cur] = _build(arr, l, m);
//         rc[cur] = _build(arr, m + 1, r);
//         tree[cur] = merge(tree[lc[cur]], tree[rc[cur]]);
//         return cur;
//     }

//     int _update(int pre, int l, int r, int pos, int val) {
//         int cur = ++ts;
//         newnode(pre, cur);
//         if (l == r) {
//             tree[cur].val += val;
//             return cur;
//         }
//         int m = (l + r) / 2;
//         if (pos <= m)
//             lc[cur] = _update(lc[pre], l, m, pos, val);
//         else
//             rc[cur] = _update(rc[pre], m + 1, r, pos, val);

//         tree[cur] = merge(tree[lc[cur]], tree[rc[cur]]);
//         return cur;
//     }

//     int _query(int cur, int pre, int l, int r, int ql, int qr) {
//         if (ql > r || qr < l)
//             return 0;
//         if (ql <= l && r <= qr)
//             return tree[cur].val - tree[pre].val;
//         int m = (l + r) / 2;
//         return _query(lc[cur], lc[pre], l, m, ql, qr) + _query(rc[cur], rc[pre], m + 1, r, ql, qr);
//     }

//     int _kth(int cur, int pre, int l, int r, int k) {
//         if (l == r)
//             return l;
//         int cnt = tree[lc[cur]].val - tree[lc[pre]].val;
//         int m = (l + r) / 2;
//         if (k <= cnt)
//             return _kth(lc[cur], lc[pre], l, m, k);
//         else
//             return _kth(rc[cur], rc[pre], m + 1, r, k - cnt);
//     }

// public:
//     std::vector<int> root;

//     PST(int n) : n(n), ts(0), lc(22 * n + 5), rc(22 * n + 5), tree(22 * n + 5), root(22 * n + 5) {}

//     int build(const std::vector<int> &arr) { return _build(arr, 1, n); }

//     int update(int pre_version, int pos, int val) { return _update(pre_version, 1, n, pos, val); }

//     int query(int cur_version, int pre_version, int l, int r) { return _query(cur_version, pre_version, 1, n, l, r);
//     }

//     int kth(int cur_version, int pre_version, int k) { return _kth(cur_version, pre_version, 1, n, k); }
// };

// void solve() {
//     int n, q;
//     cin >> n >> q;
//     vector<int> a(n + 1);
//     For(i, n) cin >> a[i + 1];

//     PST pst(n);

//     for (int i = 1; i <= n; i++) {
//         pst.root[i] = pst.update(pst.root[i - 1], a[i], 1);
//     }

//     vector<int> L(n + 2, 0);
//     for (int i = 1; i + 1 <= n; i++) {
//         L[i] = max(a[i], a[i + 1]);
//     }

//     vector<int> R(n + 2, 0);
//     for (int i = 1; i <= n - 1; i++)
//         R[i] = i;
//     for (int i = n - 1; i >= 1; i--) {
//         if (i + 2 <= n - 1 && L[i] < L[i + 2])
//             R[i] = R[i + 2];
//         else
//             R[i] = i;
//     }

//     auto check = [&](int left, int right) -> bool {
//         if (left > right)
//             return true;
//         return R[left] >= right;
//     };

//     auto get = [&](int l, int r, int k) -> int { return pst.kth(pst.root[r], pst.root[l - 1], k); };

//     vector<int> bad(n + 2, 0), pre(n + 2, 0);
//     for (int i = 1; i + 2 <= n; i++) {
//         if (a[i] > a[i + 2] && a[i + 1] > a[i + 2] && a[i + 1] < a[i])
//             bad[i] = 1;
//     }
//     for (int i = 1; i <= n; i++)
//         pre[i] = pre[i - 1] + bad[i];

//     while (q--) {
//         int l, r;
//         cin >> l >> r;
//         int len = r - l + 1;
//         if (len <= 2) {
//             cout << "YES\n";
//             continue;
//         }

//         if (r - l + 1 >= 3) {
//             int cnt = pre[r - 2] - pre[l - 1];
//             if (cnt > 0) {
//                 cout << "NO\n";
//                 continue;
//             }
//         }

//         if (len % 2 == 0) {
//             if (check(l, r - 1))
//                 cout << "YES\n";
//             else
//                 cout << "NO\n";
//         } else {
//             int mid = (l + r) / 2;
//             int kth = get(l, r, (len + 1) / 2);
//             if (a[mid] != kth) {
//                 cout << "NO\n";
//                 continue;
//             }

//             bool left = true, right = true, f1 = true, f2 = true;
//             int LL = -1;
//             if (mid - 2 >= l) {
//                 int t = mid - 2;
//                 if (((t - l) & 1) != 0)
//                     t--;
//                 if (t >= l) {
//                     left = check(l, t);
//                     LL = t;
//                 }
//             }

//             int RR = -1;
//             if (mid + 1 <= r - 1) {
//                 int s = mid + 1;
//                 right = check(s, r - 1);
//                 RR = s;
//             }

//             if (LL != -1)
//                 f1 = (L[LL] < a[mid]);
//             if (RR != -1)
//                 f2 = (a[mid] < L[RR]);

//             if (left && right && f1 && f2)
//                 cout << "YES\n";
//             else
//                 cout << "NO\n";
//         }
//     }
// }

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];

    vector<int> bad(n + 2, 0), pre(n + 2, 0);
    for (int i = 1; i + 2 <= n; i++) {
        if (a[i] > a[i + 2] && a[i + 1] > a[i + 2] && a[i + 1] < a[i])
            bad[i] = 1;
        pre[i] = pre[i - 1] + bad[i];
    }
    for (int i = n - 1; i <= n; i++)
        pre[i] = pre[i - 1] + bad[i];

    while (q--) {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;
        if (len < 3) {
            cout << "YES\n";
            continue;
        }
        int cnt = pre[r - 2] - pre[l - 1];
        cout << (cnt == 0 ? "YES\n" : "NO\n");
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
