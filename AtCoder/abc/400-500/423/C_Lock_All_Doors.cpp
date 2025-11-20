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
    int R;
    cin >> R;
    vector<int> L(n + 1);
    For(i, n) cin >> L[i + 1];

    vector<int> pre(n + 1, 0);
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + (L[i] == 1);

    int zeros = 0;
    for (int i = 1; i <= n; i++)
        if (L[i] == 0)
            zeros++;

    int left = 0;
    if (R >= 1) {
        int t = -1;
        for (int i = 1; i <= R; i++)
            if (L[i] == 0) {
                t = i;
                break;
            }
        if (t != -1)
            left = pre[R] - pre[t];
    }

    int right = 0;
    if (R < n) {
        int t = -1;
        for (int i = n; i >= R + 1; i--)
            if (L[i] == 0) {
                t = i;
                break;
            }
        if (t != -1)
            right = pre[t - 1] - pre[R];
    }

    cout << (zeros + 2 * (left + right)) << '\n';
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
