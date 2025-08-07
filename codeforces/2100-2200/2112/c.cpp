#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
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

void init() {}

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x: a)
        cin >> x;

    sort(a.begin(), a.end());
    int mx = a[n - 1];
    int ans = 0;

    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            int x = a[i], y = a[j];
            int lo = mx - x - y + 1;
            int hi = x + y;
            int cnt = lower_bound(a.begin() + j + 1, a.end(), hi) - lower_bound(a.begin() + j + 1, a.end(), lo);
            ans += max(0ll, cnt);
        }
    }

    cout << ans << '\n';
}



signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
