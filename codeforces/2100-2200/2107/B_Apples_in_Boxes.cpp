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

    int mx = ranges::max(a);
    int mn = ranges::min(a);

    int cnt = 0;
    for (int x: a) {
        if (x == mx) {
            cnt++;
        }
    }

    if (mx - mn > k + 1 || (mx - mn == k + 1 && cnt > 1)) {
        cout << "Jerry\n";
        return;
    }

    int s = accumulate(a.begin(), a.end(), 0ll);
    if (s % 2 == 0) {
        cout << "Jerry\n";
    } else {
        cout << "Tom\n";
    }
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
