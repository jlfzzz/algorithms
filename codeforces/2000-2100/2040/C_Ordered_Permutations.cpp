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
    int n, k;
    cin >> n >> k;

    int mx = 0;
    if (n - 1 < 63) {
        mx = 1ll << (n - 1);
    } else {
        mx = inf;
    }
    if (k > mx) {
        cout << -1 << '\n';
        return;
    }

    vector<int> ans(n + 1, 0);
    int left = 1;
    int right = n;
    for (int i = 1; i <= n; i++) {
        int m = inf;
        if (n - i - 1 < 63) {
            m = 1ll << (n - i - 1);
        }
    
        if (k > m) {
            ans[right] = i;
            right--;
            k -= m;
        } else {
            ans[left] = i;
            left++;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
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
