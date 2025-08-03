#include <bits/stdc++.h>
#include <climits>
#include <numeric>
#include <type_traits>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    ll h, n;
    cin >> h >> n;
    vector<ll> damage(n);
    For(i, n) { cin >> damage[i]; }
    vector<ll> cooldown(n);
    For(i, n) { cin >> cooldown[i]; }

    ll ans = 0;
    ll lo = 1;
    ll hi = 4e10 + 5;
    ll t = accumulate(damage.begin(), damage.end(), 0LL);

    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        auto check = [&](ll turn) -> bool {
            ll s = t;
            For(i, n) {
                s += 1LL * ((turn - 1) / cooldown[i]) * damage[i];
                if (s >= h) {
                    return true;
                }
            }
            return false;
        };
        if (check(mid)) {
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
