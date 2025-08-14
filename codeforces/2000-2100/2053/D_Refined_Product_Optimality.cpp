#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;
using u32 = unsigned;
static constexpr int P = 998244353;
int T, n, q;
i64 inv(i64 a, int x = P - 2) {
    i64 res = 1;
    for (; x; x >>= 1, a = a * a % P)
        if (x & 1)
            res = res * a % P;
    return res;
}
void solve() {
    cin >> n >> q;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    vector<int> u(a), v(b);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    i64 ans = 1;
    for (int i = 1; i <= n; i++)
        ans = ans * min(a[i], b[i]) % P;
    cout << ans << ' ';
    for (int op, x, p; q--;) {
        cin >> op >> x;
        if (op == 1) {
            p = upper_bound(a.begin(), a.end(), u[x]) - a.begin() - 1;
            ans = ans * inv(min(a[p], b[p])) % P;
            u[x]++;
            a[p]++;
        }
        if (op == 2) {
            p = upper_bound(b.begin(), b.end(), v[x]) - b.begin() - 1;
            ans = ans * inv(min(a[p], b[p])) % P;
            v[x]++;
            b[p]++;
        }
        ans = ans * min(a[p], b[p]) % P;
        cout << ans << ' ';
    }
    cout << '\n';
}
void init() {}

// ll power(ll base, ll exp) {
//     ll res = 1;
//     base %= MOD;
//     while (exp > 0) {
//         if (exp % 2 == 1)
//             res = (res * base) % MOD;
//         base = (base * base) % MOD;
//         exp /= 2;
//     }
//     return res;
// }

// ll modInverse(ll n) { return power(n, MOD - 2); }

// void solve() {
//     int n, q;
//     cin >> n >> q;

//     vector<int> a(n);
//     vector<int> tree_a(4 * n, 1);
//     multiset<int> b;

//     auto update = [&](this auto &&update, int o, int l, int r, int i, int val) -> int {
//         if (l == r) {
//             tree_a[o] = val;
//             return tree_a[o];
//         }

//         int m = l + (r - l) / 2;
//         if (i <= m) {
//             update(o * 2, l, m, i, val);
//         } else {
//             update(o * 2 + 1, m + 1, r, i, val);
//         }
//         tree_a[o] = tree_a[o * 2] * tree_a[o * 2 + 1] % MOD;
//         return tree_a[o];
//     };

//     auto add = [&](this auto &&add, int o, int l, int r, int i, int val) -> int {
//         if (l == r) {
//             tree_a[o] += val;
//             return tree_a[o];
//         }

//         int m = l + (r - l) / 2;
//         if (i <= m) {
//             add(o * 2, l, m, i, val);
//         } else {
//             add(o * 2 + 1, m + 1, r, i, val);
//         }
//         tree_a[o] = tree_a[o * 2] * tree_a[o * 2 + 1] % MOD;
//         return tree_a[o];
//     };

//     int prod1 = 1;
//     int prod2 = 1;
//     For(i, n) {
//         int x;
//         cin >> x;
//         update(1, 0, n - 1, i, x);
//         prod1 = prod1 * x % MOD;
//     }

//     For(i, n) {
//         int x;
//         cin >> x;
//         b.insert(x);
//         prod2 = prod2 * x % MOD;
//     }

//     vector<int> ans(q);
//     cout << min(prod1, prod2) << ' ';

//     For(i, q) {
//         int o, x;
//         cin >> o >> x;
//         x--;

//         if (o == 1) {
//             add(1, 0, n - 1, x, 1);
//             prod1 = tree_a[1];
//         } else {
//             int mn_b = *b.begin();
//             b.erase(b.begin());
//             b.insert(mn_b + 1);
//             prod2 = prod2 * modInverse(mn_b) % MOD * (mn_b + 1) % MOD;
//         }
//         ans[i] = min(prod1, prod2);
//     }
//     for (int x: ans) {
//         cout << x << ' ';
//     }
//     cout << '\n';
// }



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
