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
    vector<int> p(n + 1);
    For(i, n) cin >> p[i + 1];

    unordered_map<int, int> mp;
    for (int i = 1; i <= n; i++) {
        mp[p[i]] = i;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int x = p[i];
        if (x == i)
            continue;

        int y = p[x];
        if (y == i)
            continue;

        int z = mp[i];
        p[x] = i;
        p[z] = y;
        mp[i] = x;
        mp[y] = z;
        ans++;
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
