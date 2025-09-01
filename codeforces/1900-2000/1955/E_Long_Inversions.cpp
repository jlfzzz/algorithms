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
    string s;
    cin >> s;
    // auto f = [&](int k) -> bool {
    //     bool swapped = false;
    //     int r = -1;
    //     for (int j = 0; j < n; j++) {
    //         int curr = s[j] - '0';
    //         if (j + k <= n) {
    //             if (swapped) {
    //                 if (curr == 1) {
    //                     if (j < r) {
    //                         swapped = !swapped;
    //                         r = j + k;
    //                     } else {
    //                         continue;
    //                     }
    //                 } else {
    //                     if (j < r) {
    //                         continue;
    //                     } else {
    //                         swapped = !swapped;
    //                         r = j + k;
    //                     }
    //                 }
    //             } else {
    //                 if (curr == 1) {
    //                     continue;
    //                 } else {
    //                     swapped = !swapped;
    //                     r = j + k;
    //                 }
    //             }
    //         } else {
    //             if (swapped) {
    //                 if (curr == 1) {
    //                     if (j < r) {
    //                         return false;
    //                     } else {
    //                         continue;
    //                     }
    //                 } else {
    //                     if (j < r) {
    //                         continue;
    //                     } else {
    //                         return false;
    //                     }
    //                 }
    //             } else {
    //                 if (curr == 1) {
    //                     continue;
    //                 } else {
    //                     return false;
    //                 }
    //             }
    //         }
    //     }
    //     return true;
    // };
    auto f = [&](int k) -> bool {
        vector<int> status(n + 1);
        int pre = 0;
        for (int i = 0; i < n; i++) {
            pre ^= status[i];
            int curr = s[i] - '0';
            if (pre) {
                if (curr == 1) {
                    pre ^= 1;
                    if (i + k > n) {
                        return false;
                    }
                    status[i + k] ^= 1;
                }
            } else {
                if (curr == 0) {
                    pre ^= 1;
                    if (i + k > n) {
                        return false;
                    }
                    status[i + k] ^= 1;
                }
            }
        }
        return true;
    };
    int ans = 1;
    for (int i = 2; i <= n; i++) {
        if (f(i)) {
            ans = max(ans, i);
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
