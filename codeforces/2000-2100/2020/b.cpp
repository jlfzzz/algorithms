#include <bits/stdc++.h>
#include <cmath>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    ll k;
    cin >> k;

    ll lo = 1, hi = 2 * k + 1;
    ll ans = -1;

    auto calc = [&](ll x) -> ll {
        ll lo = 1, hi = x + 1;
        ll res = 0;
        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;
            if (mid <= x / mid) {
                res = mid;
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return res;
    };


    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        ll s = mid - calc(mid);
        if (s >= k) {
            ans = mid;
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    cout << ans << '\n';
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
