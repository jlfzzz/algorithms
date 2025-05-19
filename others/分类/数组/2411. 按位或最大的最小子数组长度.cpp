#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> smallestSubarrays(vector<int> &nums) {
        int n = nums.size();
        vector<int> ans(n);  // 存储结果
        vector<pair<int, int>> ors;  // 存储(按位或值, 对应子数组的右端点的最小值)

        // 从右往左遍历数组
        for (int i = n - 1; i >= 0; --i) {
            ors.emplace_back(0, i);  // 初始化一个新的pair，值为0，右端点为当前位置i
            ors[0].first |= nums[i];  // 更新第一个元素的按位或值

            int k = 0;  // 用于记录不同按位或值的数量

            // 遍历之前的所有按位或值，并更新
            for (int j = 1; j < ors.size(); ++j) {
                ors[j].first |= nums[i];  // 将当前位置的值与已有的按位或值进行或操作

                // 如果更新后的值与之前的某个值相同，则合并，并保留最小的右端点
                if (ors[k].first == ors[j].first) {
                    ors[k].second = ors[j].second;
                } else {
                    // 不同值，保留到结果中
                    ors[++k] = ors[j];
                }
            }

            ors.resize(k + 1);  // 调整ors大小，保留有用的信息

            // 计算当前位置的最小子数组长度
            ans[i] = ors[0].second - i + 1;
        }

        return ans;
    }
};
