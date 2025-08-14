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
    vector<pair<int, int>> ans;
    int a[n + 1] = {}, v[n];
    for (int i = 0; i < n; i++)
        cin >> v[i];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans.push_back({v[i], v[j]});
        }
        for (int j = 1; j <= n; j++) {
            if (a[j]) {
                if (j > v[i])
                    break;
                ans.push_back({v[i], j});
            }
        }
        a[v[i]] = 1;
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (auto [i, j]: ans)
        cout << i << ' ' << j << '\n';
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
