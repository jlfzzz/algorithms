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
    int n;
    cin >> n;
    int m = bit_width((ull) (n));

    if (n == 5) {
        cout << 5 << '\n';
        cout << 2 << ' ' << 1 << ' ' << 3 << ' ' << 4 << ' ' << 5 << '\n';
        return;
    }
    vector<bool> vis(n + 1, false);

    vector<int> ans;
    for (int i = m - 1; i >= 1; i--) {
        int x1 = 1 << i;
        ans.push_back(x1);
        ans.push_back(x1 - 1);
        vis[x1] = vis[x1 - 1] = true;
    }

    if (n & 1) {
        if (n != (1 << (m - 1))) {
            ans.insert(ans.begin(), n);
            vis[n] = true;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i] and i & 1) {
            ans.push_back(i);
            vis[i] = true;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            ans.push_back(i);
        }
    }
    ranges::reverse(ans);
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        if (i & 1) {
            mx &= ans[i - 1];
        } else {
            mx |= ans[i - 1];
        }
    }
    cout << mx << '\n';

    for (int x: ans)
        cout << x << ' ';

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
