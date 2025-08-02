#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int lo = 2;
    int hi = 1000;
    int ans = 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        int t;
        cout << "? " << mid << " " << mid << endl;
        cin >> t;
        if (t > mid * mid) {
            hi = mid;
        } else {
            lo = mid + 1;
            ans = mid;
        }
    }
    cout << "! " << ans + 1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
