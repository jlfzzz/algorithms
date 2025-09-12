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
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];
    ranges::sort(a);

    int cnt = 0;
    int ans = 0;
    int p = n - 1;
    for (int i = 0; i < n; i++) {
        if (i > p) {
            break;
        }
        if (i == p) {
            if (a[i] == 1) {
                ans++;
            } else {
                int half = (a[i] + 1 - cnt) / 2;
                ans += half + 1;
            }


            break;
        } else {
            if (cnt + a[i] < a[p]) {
                ans += a[i];
                cnt += a[i];
            } else if (cnt + a[i] == a[p]) {
                ans += a[i];
                cnt = 0;
                ans++;
                p--;
            } else {
                int need = a[p] - cnt;
                ans += need + 1;
                p--;
                a[i] -= need;
                cnt = 0;

                i--;
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
