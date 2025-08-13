#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    bool swapped = false;
    if (n < m) {
        swap(n, m);
        swapped = true;
    }

    if (n - m > k || n < k) {
        cout << -1 << '\n';
        return;
    }

    string ans(n + m, '0');
    int i = 0;
    bool flag = true;
    int tot = n + m;
    while (i < tot) {
        int j = i;
        if (flag) {
            for (; j < i + min(k, n); j++) {
                ans[j] = '0';
            }
            n -= min(k, n);
        } else {
            for (; j < i + min(k, m); j++) {
                ans[j] = '1';
            }
            m -= min(k, m);
        }
        flag = !flag;
        i = j;
    }

    if (swapped) {
        for (char &c: ans) {
            if (c == '0') {
                c = '1';
            } else {
                c = '0';
            }
        }
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
        solve();
    return 0;
}
