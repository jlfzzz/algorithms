#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(n + 1); // 1-based索引
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        // 必须排序！这是关键步骤
        sort(a.begin() + 1, a.end());

        // 计算保留的酒吧数量
        int remaining_bars = n - k;

        // 根据保留酒吧数量的奇偶性计算答案区间
        if (remaining_bars % 2 == 0) {
            // 偶数个保留酒吧的情况
            int left_boundary = remaining_bars / 2; // 左边界索引
            int right_boundary = remaining_bars / 2 + 1 + k; // 右边界索引

            // 答案是区间内所有整数的个数
            int answer = a[right_boundary] - a[left_boundary] + 1;
            cout << answer << "\n";
        } else {
            // 奇数个保留酒吧的情况
            int left_boundary = remaining_bars / 2 + 1; // 左边界索引（中位数）
            int right_boundary = remaining_bars / 2 + 1 + k; // 右边界索引

            // 答案是区间内所有整数的个数
            int answer = a[right_boundary] - a[left_boundary] + 1;
            cout << answer << "\n";
        }
    }

    return 0;
}
