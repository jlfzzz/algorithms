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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    For(i, n) { cin >> a[i]; }

    if (n == 1) {
        for (int i = 0; i < q; ++i) {
            int l, r;
            cin >> l >> r;
            cout << 0 << ' ';
        }
        cout << '\n';
        return;
    }

    vector<int> diff(n - 1);
    for (int i = 0; i < n - 1; i++) {
        diff[i] = abs(a[i + 1] - a[i]);
    }
    vector<int> tree(4 * n);

    auto build = [&](this auto &&build, int o, int l, int r) -> void {
        if (l == r) {
            tree[o] = diff[l];
            return;
        }
        int m = l + (r - l) / 2;
        build(o * 2, l, m);
        build(o * 2 + 1, m + 1, r);
        tree[o] = gcd(tree[o * 2], tree[o * 2 + 1]);
    };
    build(1, 0, n - 2);

    auto query = [&](this auto &&query, int o, int l, int r, int L, int R) -> int {
        if (l >= L and r <= R) {
            return tree[o];
        }

        int res = 0;
        int m = l + (r - l) / 2;
        if (L <= m) {
            res = query(o * 2, l, m, L, R);
        }
        if (R > m) {
            res = gcd(res, query(o * 2 + 1, m + 1, r, L, R));
        }
        return res;
    };

    For(i, q) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;

        if (l == r) {
            cout << 0 << ' ';
            continue;
        }

        int t = query(1, 0, n - 2, l, r - 1);
        cout << t << ' ';
    }
    cout << '\n';
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
