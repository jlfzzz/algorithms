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
    int k, x;
    cin >> k >> x;
    int S = (1ll << (k + 1));
    int half = (1ll << k);
    vector<int> ans;
    int c = x;
    if (c == half) {
        cout << 0 << '\n';
        return;
    }
    while (c != half) {
        if (c <= half) {
            ans.push_back(1);
            c = c * 2;
        } else {
            ans.push_back(2);
            c = 2 * c - S;
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    if (!ans.empty())
        for (int i = 0; i < ans.size(); i++)
            cout << ans[i] << ' ';
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
