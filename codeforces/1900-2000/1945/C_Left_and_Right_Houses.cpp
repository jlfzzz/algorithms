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
    string s;
    cin >> s;
    vector<int> pre(n + 1);
    For(i, n) { pre[i + 1] = pre[i] + (s[i] == '1'); }

    int ans = -1;
    double best = 1e9;

    for (int i = 0; i <= n; i++) {
        int L1 = pre[i];
        int R1 = pre.back() - pre[i];
        int L0 = i - L1;
        if (L0 >= (i + 1) / 2 && R1 >= (n - i + 1) / 2) {
            double diff = abs(n / 2.0 - i);
            if (ans == -1 || diff < best) {
                ans = i;
                best = diff;
            } else if (abs(diff - best) < 1e-9) {
                if (i < ans) {
                    ans = i;
                }
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
