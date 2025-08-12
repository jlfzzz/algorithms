#include <bits/stdc++.h>
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
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int x, n, m;
    cin >> x >> n >> m;
    int temp = x, t2 = n, t3 = m;
    while (m && x != 1 && x)
        x = (x + 1) / 2, m--;
    while (n && x)
        x /= 2, n--;
    cout << x << " ";
    x = temp, n = t2, m = t3;
    while (n && x)
        x /= 2, n--;
    while (m && x != 1 && x)
        x = (x + 1) / 2, m--;
    cout << x << "\n";
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
