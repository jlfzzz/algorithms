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
    For(i, n) { cin >> a[i]; }

    int ans = -1;
    int cnt = 0;
    int p = -1;
    For(i, n) {
        if (a[i] > a[(i + 1) % n]) {
            cnt += 1;
            p = i + 1;
        }
    }
    if (cnt == 0) {
        ans = 0;
    } else if (cnt == 1) {
        int res = min(p + 2, n - p);
        if (ans == -1 || ans > res) {
            ans = res;
        }
    }
    cnt = 0;
    For(i, n) {
        if (a[i] < a[(i + 1) % n]) {
            cnt += 1;
            p = i + 1;
        }
    }
    if (cnt == 0) {
        ans = 0;
    } else if (cnt == 1) {
        int res = min(p + 1, n - p + 1);
        if (ans == -1 || ans > res) {
            ans = res;
        }
    }
    cout << ans << "\n";
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
