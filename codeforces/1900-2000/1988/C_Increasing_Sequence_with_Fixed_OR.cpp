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

    int m = n;

    auto lb = [&](int x) -> int { return x & -x; };
    vector<int> ans;
    ans.push_back(n);

    while (true) {
        int t = lb(m);
        if (t == 0) {
            break;
        }
        m -= t;
        if (n - t > 0)
            ans.push_back(n - t);
    }

    ranges::sort(ans);
    cout << ans.size() << '\n';
    for (int x: ans) {
        cout << x << ' ';
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
