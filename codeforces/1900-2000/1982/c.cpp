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
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> nums(n);
    For(i, n) { cin >> nums[i]; }

    int ans = 0;
    int window = 0;
    int left = 0;
    For(right, n) {
        window += nums[right];
        if (window >= l and window <= r) {
            ans++;
            window = 0;
            left = right + 1;
            continue;
        }

        while (window > r && left <= right) {
            window -= nums[left];
            left++;
        }

        // 收缩后检查窗口是否有效
        if (left <= right && window >= l && window <= r) {
            ans++;
            window = 0;
            left = right + 1;
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
