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
    int n, k, d;
    cin >> n >> k >> d;
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];
    vector<int> v(k + 1);
    For(i, k) cin >> v[i + 1];

    int ans = 0;
    for (int i = 1; i <= min(n + n + 1, d); i++) {
        int cnt = 0;
        for (int j = 1; j <= n; j++) {
            if (a[j] == j) {
                cnt++;
            }
        }

        int left = d - i;
        int left_contri = left / 2;
        ans = max(ans, cnt + left_contri);

        int R = (i % k == 0) ? k : i % k;
        for (int j = 1; j <= v[R]; j++) {
            a[j]++;
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
