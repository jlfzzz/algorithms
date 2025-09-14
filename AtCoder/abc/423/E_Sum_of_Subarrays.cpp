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
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> pref1(n + 1, 0);
    vector<int> pref2(n + 1, 0);
    vector<int> pref3(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        pref1[i] = pref1[i - 1] + a[i];
        pref2[i] = pref2[i - 1] + i * a[i];
        pref3[i] = pref3[i - 1] + i * i * a[i];
    }

    while (q--) {
        int L, R;
        cin >> L >> R;

        int sum1 = pref1[R] - pref1[L - 1];
        int sum2 = pref2[R] - pref2[L - 1];
        int sum3 = pref3[R] - pref3[L - 1];

        int ans = -sum3 + (L + R) * sum2 - (L - 1) * (R + 1) * sum1;

        cout << ans << '\n';
    }
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
