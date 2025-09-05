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
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    For(i, n) cin >> a[i];
    For(i, m) cin >> b[i];

    int i = 0, j = 0;
    int ans = 0;
    while (i < n && j < m) {
        int x = a[i];
        int old1 = i;
        while (i < n && a[i] == x) {
            i++;
        }

        int cnt1 = i - old1;

        // if (a[i] != b[j]) {
        //     cout << -1 << '\n';
        //     return;
        // }

        int old = j;

        while (j < m && b[j] == x) {
            j++;
        }


        int cnt2 = j - old;

        int d = cnt2 - cnt1;

        if (d < 0) {
            cout << -1 << '\n';
            return;
        }

        int need = 0;
        while (cnt1 < cnt2) {
            need++;
            cnt1 = cnt1 * 2;
        }

        ans = max(ans, need);

        // i++;
    }

    if (i != n || j != m) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
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
