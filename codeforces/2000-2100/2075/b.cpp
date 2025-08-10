#include <bits/stdc++.h>
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
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    For(i, n) { cin >> nums[i]; }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        // 创建左右两部分的数组
        vector<int> left, right;
        for (int j = 0; j < i; j++) {
            left.push_back(nums[j]);
        }
        for (int j = i + 1; j < n; j++) {
            right.push_back(nums[j]);
        }

        // 对左右两部分分别排序（降序）
        ranges::sort(left, [](int a, int b) { return a > b; });
        ranges::sort(right, [](int a, int b) { return a > b; });

        // 特殊情况：i=0或i=n-1时，可以从一边选择所有元素
        if (i == 0 || i == n - 1) {
            vector<int> temp;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    temp.push_back(nums[j]);
                }
            }
            ranges::sort(temp, [](int a, int b) { return a > b; });

            long long sum = 0;
            For(j, k) { sum += temp[j]; }
            sum += nums[i];
            ans = max(ans, (int) sum);
        }
        // 一般情况：必须左右都至少选一个
        else {
            if (left.empty() || right.empty() || k > left.size() + right.size()) {
                continue; // 无法满足条件
            }

            // 合并左右两边的最大元素，但确保左右都至少选一个
            vector<pair<int, int>> candidates; // {value, side} 0=left, 1=right
            for (int val: left)
                candidates.push_back({val, 0});
            for (int val: right)
                candidates.push_back({val, 1});

            ranges::sort(candidates,
                         [](const pair<int, int> &a, const pair<int, int> &b) { return a.first > b.first; });

            // 选择前k个，但必须左右都有
            long long sum = nums[i];
            int leftCount = 0, rightCount = 0;
            for (int j = 0; j < k && j < candidates.size(); j++) {
                sum += candidates[j].first;
                if (candidates[j].second == 0)
                    leftCount++;
                else
                    rightCount++;
            }

            // 检查是否左右都至少有一个
            if (leftCount > 0 && rightCount > 0) {
                ans = max(ans, (int) sum);
            }
        }
    }
    cout << ans << '\n';
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
