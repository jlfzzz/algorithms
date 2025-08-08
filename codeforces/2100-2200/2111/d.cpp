#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll

void init() {}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> nums(m);
    For(i, m) {
        int a;
        cin >> a;
        nums[i] = a;
    }

    ranges::sort(nums);
    vector<vector<int>> ans(n, vector<int>(6));

    for (int i = 0; i < n / 2; i++) {
        int x = nums[i];
        int y = nums[m - i - 1];
        for (int j = 0; j < 6; j++) {
            if (j & 1) {
                ans[i][j] = x;
                ans[n - i - 1][j] = y;
            } else {
                ans[i][j] = y;
                ans[n - 1 - i][j] = x;
            }
        }
    }
    if (n & 1) {
        if (m == n) {
            for (int i = 0; i < 6; i++) {
                ans[n / 2][i] = nums[n / 2];
            }
        } else {
            for (int i = 0; i < 6; i++) {
                if (i & 1) {
                    ans[n / 2][i] = nums[n / 2];
                } else {
                    ans[n / 2][i] = nums[m - 1 - n / 2];
                }
            }
        }
    }

    For(i, n) {
        For(j, 6) { cout << ans[i][j] << ' '; }
        cout << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
