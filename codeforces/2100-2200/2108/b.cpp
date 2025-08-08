#include <bit>
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

void init() {}
int t, n, x;
int solve() {
    if (n == 1)
        return (x ? x : -1);
    if (!x)
        return ((n & 1) ? n + 3 : n);
    if (x == 1)
        return ((n & 1) ? n : n + 3);
    int ans = x;
    while (x)
        n -= (x & 1), x >>= 1;
    if (n <= 0)
        return ans;
    return ans + n + (n & 1);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n >> x;
        cout << solve() << '\n';
    }
    return 0;
}
