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
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int q;
    cin >> q;

    vector<int> nxt(n + 1, -1);
    vector<int> stk;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        while (!stk.empty() && x != a[stk.back()]) {
            int y = stk.back();
            stk.pop_back();
            nxt[y] = i;
        }

        stk.push_back(i);
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        l--, r--;

        if (a[l] != a[r]) {
            cout << l + 1 << ' ' << r + 1 << '\n';
            continue;
        }

        int nxt_i = nxt[l];
        if (nxt_i != -1 && nxt_i <= r) {
            cout << l + 1 << ' ' << nxt_i + 1 << '\n';
        } else {
            cout << -1 << ' ' << -1 << '\n';
        }
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
