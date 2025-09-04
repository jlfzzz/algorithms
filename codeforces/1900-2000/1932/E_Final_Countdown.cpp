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
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + (s[i - 1] - '0');
    }

    vector<int> ans(n + 1);
    int carry = 0;
    for (int i = n; i >= 0; i--) {
        int curr = carry + pre[i];
        ans[i] = curr % 10;
        carry = curr / 10;
    }

    int i = 0;
    while (ans[i] == 0) {
        i++;
    }

    for (; i <= n; i++) {
        cout << ans[i];
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
