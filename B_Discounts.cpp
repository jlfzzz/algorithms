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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(k);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < k; i++) {
        cin >> b[i];
    }

    ranges::sort(b);
    ranges::sort(a);
    ranges::reverse(a);

    int j = 0;
    int i = 0;
    int ans = 0;
    while (i < n && j < k) {
        int t = b[j];
        if (i + t > n) {
            break;
        }
        for (int l = 0; l < t - 1; l++) {
            ans += a[i + l];
        }
        i += t;
        j++;
    }

    while (i < n) {
        ans += a[i];
        i++;
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
