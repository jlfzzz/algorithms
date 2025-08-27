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
    vector<int> a(n), b(n);
    For(i, n) cin >> a[i];
    For(i, n) cin >> b[i];

    auto ta = a, tb = b;
    ranges::sort(ta), ranges::sort(tb);
    if (ta != tb) {
        cout << "NO\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        a[i] = ranges::lower_bound(ta, a[i]) - ta.begin() + 1;
        b[i] = ranges::lower_bound(tb, b[i]) - tb.begin() + 1;
    }

    int mx = ranges::max(a);

    vector<int> treeA(mx + 1), treeB(mx + 1);
    auto add = [&](vector<int> &v, int i) {
        for (; i <= mx; i += i & -i) {
            v[i]++;
        }
    };

    auto query = [&](vector<int> &v, int i) -> int {
        int res = 0;
        while (i) {
            res += v[i];
            i -= i & -i;
        }
        return res;
    };

    auto f = [&](vector<int> &v, vector<int> &tree) -> int {
        int res = 0;
        for (int i = 0; i < n; i++) {
            // int r = query(tree, mx);
            int l = query(tree, v[i]);
            res += i - l;
            add(tree, v[i]);
        }
        return res;
    };

    int t1 = f(a, treeA), t2 = f(b, treeB);
    if (((t1 & 1) ^ (t2 & 1)) == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
