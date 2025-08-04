#include <bits/stdc++.h>
#include <climits>
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

    bool f = true;
    for (int x: nums) {
        if (x != nums[0]) {
            f = false;
        }
    }
    if (f) {
        cout << -1 << '\n';
        return;
    }

    int ans = 1e9;
    vector<int> t;
    t.push_back(-1);
    for (int i = 1; i < n - 1; i++) {
        if (nums[i] != nums[i - 1] and nums[i] != nums[i + 1] and nums[i] != nums[0]) {
            t.push_back(i);
        }
    }
    t.push_back(n);

    for (int i = 1; i < t.size(); i++) {
        ans = min(ans, t[i] - t[i - 1] - 1);
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
