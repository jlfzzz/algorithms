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

int a[44], b[44];
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) // 输入
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }
    vector<pair<int, int>> ans; // 定义答案数组，用 vector 存储
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            if (a[j] > a[j + 1]) // 通过两两比较排序
            {
                swap(a[j], a[j + 1]);
                ans.push_back({1, j}); // 用 pair 存储答案
            }
        }
    }
    for (int i = 1; i < n; ++i) // 同上
    {
        for (int j = 1; j < n; ++j) {
            if (b[j] > b[j + 1]) {
                swap(b[j], b[j + 1]);
                ans.push_back({2, j});
            }
        }
    }
    for (int i = 1; i <= n; ++i) // 交换 a[i],b[i]
    {
        if (a[i] > b[i]) {
            swap(a[i], b[i]);
            ans.push_back({3, i});
        }
    }
    cout << ans.size() << endl; // 输出操作次数
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i].first << " " << ans[i].second << endl; // 输出操作内容
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
