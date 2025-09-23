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

int pow2[65];

void init() {
    pow2[0] = 1;
    for (int i = 1; i < 63; i++) {
        pow2[i] = pow2[i - 1] * 2;
    }
}

void solve() {
    int target;
    cin >> target;

    int top = 63 - __builtin_clzll(target);
    vector<int> ans;
    for (int i = 0; i < top; i++)
        ans.emplace_back(i);
    for (int i = top - 1; i >= 0; i--)
        if ((target >> i) & 1)
            ans.emplace_back(i);
    cout << ans.size() << '\n';
    for (int i: ans)
        cout << i << ' ';
    cout << '\n';

    // int lim = 1e9 - 100;
    // vector<int> ans;
    // target--;

    // while (target) {
    //     vector<int> cur;
    //     // for (int i = 0; i < 63; i++) {
    //     //     if (target >> i & 1) {
    //     //         if (i == 0) {
    //     //             cur.push_back(1);
    //     //         } else if (i == 1) {
    //     //             cur.push_back(1);
    //     //             cur.push_back(1);
    //     //         } else {
    //     //             cur.push_back(1 << i);
    //     //             nxt++;
    //     //         }
    //     //     }
    //     // }

    //     for (int i = 62; i >= 1; i--) {
    //         int have = (1 << i) - 1;
    //         if (target < have) {
    //             continue;
    //         }

    //         cur.push_back(1 << i);
    //         target -= have;
    //     }

    //     for (int x: cur) {
    //         int j = ranges::lower_bound(pow2, x) - pow2;

    //         // cout << "x is: " << x << "  j is: " << j << '\n';
    //         for (int k = 0; k < j; k++) {
    //             ans.push_back(lim);
    //             lim++;
    //         }

    //         lim -= 200;
    //     }
    // }

    // vector<int> cur;
    // int extra = 0;
    // for (int i = 62; i >= 0; i--) {
    //     if (target >> i & 1) {
    //         cur.push_back(1 << i);
    //         if (i) {
    //             extra++;
    //         }
    //     }
    // }

    // for (int x : cur) 

    // cout << ans.size() << '\n';
    // for (int x: ans) {
    //     cout << x << ' ';
    // }
    // cout << '\n';
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
