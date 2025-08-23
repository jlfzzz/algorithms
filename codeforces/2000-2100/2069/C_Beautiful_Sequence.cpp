#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(998244353);
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

constexpr int N = 2e5 + 5;
int pow2[N];

void init() {
    pow2[0] = 1;
    for (int i = 1; i < N; i++) {
        pow2[i] = pow2[i - 1] * 2 % MOD;
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int cnt1 = 0, sum = 0;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        if (x == 2) {
            sum = ((sum * 2 % MOD) + cnt1) % MOD;
        } else if (x == 1) {
            cnt1++;
        } else {
            ans = (ans + sum) % MOD;
        }
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
