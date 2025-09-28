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
    int n, sum;
    cin >> n >> sum;

    if (sum < n) {
        cout << -1 << '\n';
        return;
    }

    if (sum <= 4 * n) {
        vector<int> ans(n, 1);
        sum -= n;
        for (int i = 0; i < n; i++) {
            if (sum >= 3) {
                sum -= 3;
                ans[i] = 4;
            } else {
                break;
            }
        }

        for (int x: ans) {
            cout << x << ' ';
        }
        cout << '\n';
        return;
    }

    bool flag = true;
    int offset = 4;
    vector<int> ans(n);
    while (sum >= offset) {
        for (int i = 0; i < n; i++) {
            ans[i] += offset;
            sum -= offset;
            if (sum < offset)
                break;
        }
        if (sum < offset)
            break;
        if (!flag) {
            offset *= 10;
        }
        flag = !flag;
    }

    for (int x: ans) {
        cout << x << ' ';
    }
    cout << '\n';
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
