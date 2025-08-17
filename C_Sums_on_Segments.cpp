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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) { cin >> a[i]; }

    unordered_set<int> ans;
    ans.insert(0); // 空子数组的和为 0

    int pos = -1;
    For(i, n) {
        if (a[i] != -1 && a[i] != 1) {
            pos = i;
            break;
        }
    }

    // 情况一：没有特殊数
    if (pos == -1) {
        if (n > 0) {
            // 对整个数组使用 Kadane 算法找到最小和最大的子数组和
            int min_sum = a[0], max_sum = a[0];
            int current_min = a[0], current_max = a[0];
            for (int i = 1; i < n; i++) {
                current_min = min(a[i], current_min + a[i]);
                current_max = max(a[i], current_max + a[i]);
                min_sum = min(min_sum, current_min);
                max_sum = max(max_sum, current_max);
            }
            // 因为 1/-1 数组的和是连续的，所以直接添加范围
            for (int i = min_sum; i <= max_sum; i++) {
                ans.insert(i);
            }
        }
    }
    // 情况二：有特殊数
    else {
        // 1. 计算左边部分的子数组和
        if (pos > 0) {
            int left_min = a[0], left_max = a[0];
            int current_min = a[0], current_max = a[0];
            for (int i = 1; i < pos; i++) {
                current_min = min(a[i], current_min + a[i]);
                current_max = max(a[i], current_max + a[i]);
                left_min = min(left_min, current_min);
                left_max = max(left_max, current_max);
            }
            for (int i = left_min; i <= left_max; i++) {
                ans.insert(i);
            }
        }

        // 2. 计算右边部分的子数组和
        if (pos < n - 1) {
            int right_min = a[pos + 1], right_max = a[pos + 1];
            int current_min = a[pos + 1], current_max = a[pos + 1];
            for (int i = pos + 2; i < n; i++) {
                current_min = min(a[i], current_min + a[i]);
                current_max = max(a[i], current_max + a[i]);
                right_min = min(right_min, current_min);
                right_max = max(right_max, current_max);
            }
            for (int i = right_min; i <= right_max; i++) {
                ans.insert(i);
            }
        }

        // 3. 计算跨越 pos 的子数组和
        // 公式: (左边后缀和) + a[pos] + (右边前缀和)
        int current_sum = 0;
        int left_mn = 0, left_mx = 0;
        for (int i = pos - 1; i >= 0; i--) {
            current_sum += a[i];
            left_mx = max(left_mx, current_sum);
            left_mn = min(left_mn, current_sum);
        }

        current_sum = 0;
        int right_mn = 0, right_mx = 0;
        for (int i = pos + 1; i < n; i++) {
            current_sum += a[i];
            right_mx = max(right_mx, current_sum);
            right_mn = min(right_mn, current_sum);
        }

        for (int j = left_mn + right_mn + a[pos]; j <= left_mx + right_mx + a[pos]; j++) {
            ans.insert(j);
        }
    }

    // 输出结果
    vector<int> t;
    t.reserve(ans.size());
    for (int x: ans) {
        t.push_back(x);
    }

    cout << t.size() << '\n';
    sort(t.begin(), t.end());
    for (size_t i = 0; i < t.size(); ++i) {
        cout << t[i] << (i == t.size() - 1 ? "" : " ");
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
