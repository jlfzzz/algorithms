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
    int n, q;
    cin >> n >> q;
    struct Node {
        int sum, one;
    };

    vector<Node> tree(4 * n + 100);

    auto merge = [&](int l, int r) -> Node { return {tree[l].sum + tree[r].sum, tree[l].one | tree[r].one}; };

    auto update = [&](this auto &&update, int o, int l, int r, int i, int val) -> void {
        if (l == r) {
            tree[o] = {val, val == 1 ? 1 : 0};
            return;
        }

        int m = (l + r) / 2;
        if (i <= m) {
            update(o * 2, l, m, i, val);
        } else {
            update(o * 2 + 1, m + 1, r, i, val);
        }
        tree[o] = merge(o * 2, o * 2 + 1);
    };

    auto first_one = [&](this auto &&first_one, int o, int l, int r) -> int {
        if (l == r) {
            return l;
        }

        int m = (l + r) / 2;
        if (tree[o * 2].one) {
            return first_one(o * 2, l, m);
        }
        return first_one(o * 2 + 1, m + 1, r);
    };
    auto last_one = [&](this auto &&last_one, int o, int l, int r) -> int {
        if (l == r) {
            return l;
        }

        int m = (l + r) / 2;
        if (tree[o * 2 + 1].one) {
            return last_one(o * 2 + 1, m + 1, r);
        }
        return last_one(o * 2, l, m);
    };

    auto query = [&](this auto &&query, int o, int l, int r, int L, int R) -> int {
        if (R < l || L > r) {
            return 0;
        }

        if (l >= L && r <= R) {
            return tree[o].sum;
        }

        int m = (l + r) / 2;
        return query(o * 2, l, m, L, R) + query(o * 2 + 1, m + 1, r, L, R);
    };

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[i] = x;
        update(1, 1, n, i, x);
    }

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int s;
            cin >> s;

            int sum = tree[1].sum;
            if (s > sum) {
                cout << "NO\n";
                continue;
            }

            if (s % 2 == sum % 2) {
                if (s <= sum)
                    cout << "YES\n";
                else
                    cout << "NO\n";
            } else {
                int i1 = first_one(1, 1, n);
                int i2 = last_one(1, 1, n);
                if (a[i1] != 1) {
                    cout << "NO\n";
                } else {
                    int s1 = query(1, 1, n, 1, i1);
                    int s2 = query(1, 1, n, i2, n);
                    sum = max(sum - s1, sum - s2);
                    if (s <= sum) {
                        cout << "YES\n";
                    } else
                        cout << "NO\n";
                }
            }

        } else {
            int i, v;
            cin >> i >> v;

            if (a[i] == v) {
                continue;
            }
            a[i] = v;
            update(1, 1, n, i, v);
        }
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
