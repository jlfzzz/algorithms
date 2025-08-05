#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;

void init() {}

// 检查数组是否为回文
bool isPalindrome(const vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n / 2; i++) {
        if (arr[i] != arr[n - 1 - i]) {
            return false;
        }
    }
    return true;
}

// 通过删除x来尝试构造回文，返回剩余元素个数，-1表示无法构造
int deleteXToPalindrome(vector<int> arr, int x) {
    int n = arr.size();
    int left = 0, right = n - 1;
    int remaining = n;

    while (left < right) {
        if (arr[left] == arr[right]) {
            left++;
            right--;
        } else {
            // 尝试删除左边的x
            //bool leftDeleted = false;
            while (left < right && arr[left] == x && arr[left] != arr[right]) {
                left++;
                remaining--;
                //leftDeleted = true;
            }

            // 如果左边删除后还不匹配，尝试删除右边的x
            if ((left < right && arr[left] != arr[right])) {
                while (left < right && arr[right] == x && arr[left] != arr[right]) {
                    right--;
                    remaining--;
                }
            }

            // 如果还是不匹配，无解
            if (left < right && arr[left] != arr[right]) {
                return -1;
            }

            // 匹配成功，继续
            if (left < right) {
                left++;
                right--;
            }
        }
    }

    return remaining;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    For(i, n) { cin >> a[i]; }

    if (k == 1) {
        // k=1 时，可以删除所有元素，空数组是回文
        cout << "YES\n";
        return;
    }

    // 找到全局第k-1小和第k小的元素
    vector<int> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());

    int kth_min_1 = sorted_a[k - 2]; // 第k-1小
    int kth_min = sorted_a[k - 1]; // 第k小

    // 构建候选数组：所有 <= 第k小的元素
    vector<int> candidates;
    For(i, n) {
        if (a[i] <= kth_min) {
            candidates.push_back(a[i]);
        }
    }

    if (kth_min_1 != kth_min) {
        // 情况1: 第k-1小 != 第k小
        // 只保留 <= 第k-1小的元素，检查是否已经是回文
        vector<int> result;
        For(i, n) {
            if (a[i] <= kth_min_1) {
                result.push_back(a[i]);
            }
        }

        if (isPalindrome(result)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    } else {
        // 情况2: 第k-1小 == 第k小
        // 可以通过删除一些值为kth_min的元素来构造回文
        int remaining = deleteXToPalindrome(candidates, kth_min);

        if (remaining >= k - 1) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
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
