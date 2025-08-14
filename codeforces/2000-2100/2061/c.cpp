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

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<ll> dp_truth(n, 0);
    vector<ll> dp_lie(n, 0);

    if (a[0] == 0) {
        dp_truth[0] = 1;
    }
    dp_lie[0] = 1;

    for (int i = 1; i < n; i++) {
        ll from_truth = 0;
        ll from_lie = 0;

        if (a[i] == a[i - 1]) {
            from_truth = dp_truth[i - 1];
        }

        // 来源B: i-1 说谎。要求谎言数不变，即 a[i] == a[i-2] + 1
        if (i >= 2) { // 必须至少有 i-2
            if (a[i] == a[i - 2] + 1) {
                from_lie = dp_lie[i - 1];
            }
        } else { // i=1 的情况，前一个人是i-1=0。0说谎，谎言数是0+1=1
            if (a[i] == 1) {
                from_lie = dp_lie[i - 1];
            }
        }

        dp_truth[i] = (from_truth + from_lie) % MOD;
        dp_lie[i] = dp_truth[i - 1];
    }

    ll ans = (dp_truth[n - 1] + dp_lie[n - 1]) % MOD;
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
