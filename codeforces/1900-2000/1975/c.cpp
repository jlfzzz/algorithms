#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    For(i, n) { cin >> nums[i]; }


    int ans = 0;
    if (n == 2) {
        ans = min(nums[0], nums[1]);
    } else {
        For(i, n - 2) {
            vector<int> t{nums[i], nums[i + 1], nums[i + 2]};
            ranges::sort(t);
            ans = max(ans, t[1]);
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
