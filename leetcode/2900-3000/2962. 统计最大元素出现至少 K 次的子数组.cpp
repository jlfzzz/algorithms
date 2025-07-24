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
#include <bitset>

using namespace std;

class Solution {
public:
    long long countSubarrays(vector<int> &nums, int k) {
        int n = nums.size();
        if (n == 0 || k <= 0) {
            return 0;
        }

        // 找到最大值 mx
        // 使用 C++20 的 ranges::max
        int mx = 0;
        if (!nums.empty()) {
            mx = ranges::max(nums);
            // 或者使用 algorithm 库的 max_element
            // mx = *max_element(nums.begin(), nums.end());
        } else {
            return 0; // 理论上不会执行到这里，但为了安全
        }


        long long ans = 0;
        int cnt_mx = 0; // 窗口 [left, right] 中 mx 的数量
        int left = 0;   // 窗口左边界

        for (int right = 0; right < n; ++right) {
            // 扩大窗口，加入 nums[right]
            cnt_mx += nums[right] == mx;

            // 只要当前窗口 [left, right] 满足条件 (cnt_mx >= k)
            while (cnt_mx >= k) {
                // 找到一个有效的起始点 left，对于当前 right
                // 所有以 left 开头，以 right 或更后的位置结尾的子数组都满足条件
                // 这样的子数组有 n - right 个
                ans += (long long)(n - right);

                // 尝试缩小窗口，将 left 右移
                cnt_mx -= nums[left] == mx;
                left++;
            }
            // 循环结束后，窗口 [left, right] 的 mx 数量 < k
            // 继续移动 right
        }

        return ans;
    }
};