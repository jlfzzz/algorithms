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
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];

    multiset<int> suf, pre;
    for (int i = 1; i <= n; i++) {
        suf.insert(a[i] + i - 1);
    }

    int ans = inf;
    for (int i = 1; i <= n; i++) {
        suf.erase(suf.find(a[i] + i - 1));
        int R = suf.empty() ? 0 : *(prev(suf.end()));
        int L = pre.empty() ? 0 : *(prev(pre.end()));

        ans = min(ans, max({L, R, a[i]}));

        pre.insert(a[i] + n - i);
    }

    cout << ans << '\n';
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
