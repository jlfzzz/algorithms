#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>
#include <queue>
#include <cstring>
#include <array> 

using namespace std;

class Solution {
public:
    vector<int> getTriggerTime(vector<vector<int>> &increase, vector<vector<int>> &requirements) {
        int n = increase.size();
        int m = requirements.size();

        // 1. 计算累积属性和 (前缀和)
        vector<vector<long long>> cumulative_scores(n + 1, vector<long long>(3, 0));
        for (int i = 0; i < n; ++i) {
            cumulative_scores[i + 1][0] = cumulative_scores[i][0] + increase[i][0];
            cumulative_scores[i + 1][1] = cumulative_scores[i][1] + increase[i][1];
            cumulative_scores[i + 1][2] = cumulative_scores[i][2] + increase[i][2];
        }

        vector<int> ans(m);

        // 2. 对每个 requirement 进行二分查找
        for (int i = 0; i < m; ++i) {
            long long req_c = requirements[i][0];
            long long req_r = requirements[i][1];
            long long req_h = requirements[i][2];

            // 特殊情况：如果需求为 [0, 0, 0]，第 0 天就满足
            if (req_c == 0 && req_r == 0 && req_h == 0) {
                ans[i] = 0;
                continue;
            }

            // 二分查找：使用你的逻辑结构
            // 查找范围是天数 [1, n]。我们搜索索引，对应范围是 [1, n]。
            // 使用开区间 [left, right)，left 从 1 开始，right 从 n+1 开始
            int left = 1;
            int right = n + 1; // right 是开区间边界

            while (left < right) {
                int mid = left + (right - left) / 2; // mid 是一个潜在的天数索引

                // 检查第 mid 天是否 *不满足* 条件
                if (cumulative_scores[mid][0] < req_c ||
                    cumulative_scores[mid][1] < req_r ||
                    cumulative_scores[mid][2] < req_h) {
                    // 如果第 mid 天不满足，那么满足条件的最早一天肯定在 mid 之后
                    left = mid + 1;
                } else {
                    // 如果第 mid 天满足，那么满足条件的最早一天可能是 mid 或在 mid 之前
                    // 所以我们将搜索范围缩小到 [left, mid)
                    right = mid;
                }
            }

            // 循环结束后, left 指向第一个满足条件的天数索引
            // 或者如果所有天数都不满足，left 会等于 n + 1

            if (left > n) { // 如果 left 超出范围，说明没有找到
                ans[i] = -1;
            } else {
                // left 就是满足条件的最早天数
                ans[i] = left;
            }
        }

        return ans;
    }
};