#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;

// 返回 {答案, 选择的星星数量}
pair<int, int> solve1(ll l, ll r, ll k) {
    // 如果区间长度小于k，无法处理
    if ((r - l + 1) < k)
        return {0, 0};

    if ((r - l + 1) % 2) {
        // 奇数长度情况
        ll mid = (l + r) / 2;

        // 递归计算左半部分 [l, mid-1]
        pair<int, int> x = solve1(l, mid - 1, k);

        // 右半部分的答案可以通过对称性计算
        // 关键观察：右半部分每个被选择的星星的编号 = 对应左半部分的编号 + offset
        // offset = (r-l+1)/2 + 1 = 区间长度的一半 + 1
        ll offset = (r - l + 1) / 2 + 1;
        ll rgt_ans = offset * x.second + x.first;

        // 总答案 = 左半答案 + 右半答案 + 中间星星
        // 总选择数 = 左半选择数 * 2 + 1（中间的那个）
        return {x.first + rgt_ans + mid, x.second * 2 + 1};
    } else {
        // 偶数长度情况
        ll mid = (l + r) / 2;

        // 递归计算左半部分 [l, mid]
        pair<int, int> x = solve1(l, mid, k);

        // 右半部分的答案计算
        ll offset = (r - l + 1) / 2;
        ll rgt_ans = offset * x.second + x.first;

        // 总答案 = 左半答案 + 右半答案
        // 总选择数 = 左半选择数 * 2
        return {x.first + rgt_ans, x.second * 2};
    }
}

signed main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        cout << solve1(1, n, k).first << endl;
    }
    return 0;
}

/*
为什么这个算法是正确的？

关键在于对称性：
1. 对于区间[l,r]，左半部分和右半部分的结构是对称的
2. 如果左半部分选择了某些位置，右半部分也会选择对应的对称位置
3. 右半部分被选择位置的值 = 左半部分对应位置的值 + offset

例子分析：
区间[1,7]，长度为7（奇数）
- 中间值：4
- 左半部分：[1,3]，如果选择了位置2，贡献2
- 右半部分：[5,7]，对应选择位置6，贡献6
- offset = 7/2 + 1 = 4，所以 6 = 2 + 4

区间[1,6]，长度为6（偶数）
- 左半部分：[1,3]
- 右半部分：[4,6]
- offset = 6/2 = 3

时间复杂度：O(log n)
- 每次递归区间长度减半
- 只递归一边（左半部分）
- 右半部分通过数学公式直接计算
*/
