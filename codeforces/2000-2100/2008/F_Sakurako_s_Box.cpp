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
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int sum = accumulate(a.begin(), a.end(), 0ll);
    i128 ans = 0;
    for (int i = 0; i < n - 1; i++) {
        int x = a[i];
        sum -= x;
        ans = (ans + ((i128) x * sum % MOD)) % MOD;
    }

    auto q_pow = [&](int base, int exp) -> int {
        int res = 1;
        while (exp) {
            if (exp & 1) {
                res = res * base % MOD;
            }
            base = base * base % MOD;
            exp /= 2;
        }
        return res;
    };

    int denominator = (n * (n - 1) / 2) % MOD;
    cout << (int) ans * q_pow(denominator, MOD - 2) % MOD << '\n';
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
