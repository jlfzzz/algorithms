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

set<int> all_ones;
void init() {
    for (int base = 2; base <= 1000000; base++) {
        ll num = 1 + base + base * base;
        ll term = base * base;

        if (num > inf)
            break;

        while (num <= inf) {
            all_ones.insert(num);
            if (term > inf / base)
                break;
            term *= base;
            if (num > inf - term)
                break;
            num += term;
        }
    }
}

void solve() {
    int n;
    cin >> n;

    int lo = 1;
    int hi = 1e6 + 10;
    int target = 1;

    if (all_ones.count(n)) {
        cout << "YES" << '\n';
        return;
    }
    // while (lo < hi) {
    //     int mid = (lo + hi) / 2;
    //     if (mid * mid * mid <= n) {
    //         target = mid;
    //         lo = mid + 1;
    //     } else {
    //         hi = mid;
    //     }
    // }

    // for (int i = 2; i <= target; i++) {
    //     int t = n;
    //     bool f = true;
    //     while (t) {
    //         if (t % i != 1) {
    //             f = false;
    //             break;
    //         }
    //         t /= i;
    //     }

    //     if (f) {
    //         cout << "YES" << '\n';
    //         return;
    //     }
    // }

    int t = 4 * n - 3;
    lo = 2;
    hi = 2000000000LL + 1000;
    target = 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;

        if (mid * mid <= t) {
            target = mid;
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    if (target * target == t) {
        if ((target - 1) % 2 == 0) {
            int k = (target - 1) / 2;
            if (k > 1) {
                cout << "YES\n";
                return;
            }
        }
    }

    cout << "NO\n";
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
