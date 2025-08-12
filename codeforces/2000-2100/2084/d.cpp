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
    int n, m, k;
    cin >> n >> m >> k;

    int l = n / (m + 1);
    int deletions_per_op = (k + l - 1) / l; // ceil(k/l)
    int T1 = n / ((m + 1) * deletions_per_op);

    // at least k
    int T2 = k;

    int T = max({T1, T2, 1ll}); // 至少为1

    For(i, n) { cout << i % T << ' '; }
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
