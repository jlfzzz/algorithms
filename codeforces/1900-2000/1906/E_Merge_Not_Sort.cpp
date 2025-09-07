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
    vector<int> c(2 * n);
    For(i, 2 * n) cin >> c[i];

    vector<int> seg(2 * n);

    vector<pair<int, int>> blk;
    int head = 0;
    for (int i = 1; i < 2 * n; i++) {
        if (c[i] > c[head]) {
            seg[head] = i - head;
            blk.emplace_back(head, i - head);
            head = i;
        }
    }
    seg[head] = 2 * n - head;
    blk.emplace_back(head, 2 * n - head);

    int m = (int) blk.size();
    vector<int> dp(n + 1, -1);
    dp[0] = -2;
    for (int k = 0; k < m; k++) {
        int w = blk[k].second;
        for (int x = n; x >= w; x--) {
            if (dp[x] == -1 && dp[x - w] != -1)
                dp[x] = k;
        }
    }

    if (dp[n] == -1) {
        cout << -1 << '\n';
        return;
    }

    vector<char> take(m, 0);
    int x = n;
    while (x > 0) {
        int k = dp[x];
        take[k] = 1;
        x -= blk[k].second;
    }

    vector<int> A, B;
    for (int k = 0; k < m; k++) {
        int s = blk[k].first, len = blk[k].second;
        if (take[k]) {
            for (int t = 0; t < len; t++)
                A.push_back(c[s + t]);
        } else {
            for (int t = 0; t < len; t++)
                B.push_back(c[s + t]);
        }
    }

    For(i, n) cout << A[i] << (i + 1 == n ? '\n' : ' ');
    For(i, n) cout << B[i] << (i + 1 == n ? '\n' : ' ');
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
