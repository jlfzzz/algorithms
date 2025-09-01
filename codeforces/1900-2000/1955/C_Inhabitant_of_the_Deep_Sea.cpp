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
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int ans = 0;
    int l = 0, r = n - 1;
    while (true) {
        if (l == r) {
            if (k >= a[l]) {
                ans++;
            }
            break;
        } else {
            if (a[l] <= a[r]) {
                if (k < 2 * a[l] - 1) {
                    break;
                } else {
                    ans++;
                    a[r] -= a[l];
                    k -= 2 * a[l];
                    l++;
                }
            } else {
                if (k < 2 * a[r]) {
                    break;
                } else {

                    ans++;
                    a[l] -= a[r];
                    k -= 2 * a[r];
                    r--;
                }
            }
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
