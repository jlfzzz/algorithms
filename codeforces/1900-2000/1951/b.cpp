#include <bits/stdc++.h>
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
    int n, k;
    cin >> n >> k;
    vector<int> nums(n + 1);
    For(i, n) { cin >> nums[i + 1]; }

    vector<int> t = nums;
    swap(t[1], t[k]);
    int i = 2;
    int ans = 0;

    while (i <= n and t[1] > t[i]) {
        i++;
    }

    ans = i - 2;

    int pos = 1;
    for (int i = 1; i < k; i++) {
        if (nums[i] > nums[k]) {
            swap(nums[i], nums[k]);
            pos = i;
            break;
        }
    }

    if (pos != 1) {
        int cnt = 1;
        int i = pos + 1;
        while (i <= n and nums[i] < nums[pos]) {
            i++;
            cnt++;
        }
        ans = max(ans, cnt);
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
