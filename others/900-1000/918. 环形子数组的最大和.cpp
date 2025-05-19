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
#include <limits> 

using namespace std;

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }

        int total_sum = 0;
        int max_so_far = numeric_limits<int>::min(); // Kadane's for max subarray sum
        int current_max = 0;
        int min_so_far = numeric_limits<int>::max(); // Kadane's for min subarray sum
        int current_min = 0;

        for (int x : nums) {
            // Calculate total sum
            total_sum += x;

            // Kadane's algorithm for maximum subarray sum
            current_max = max(x, current_max + x);
            max_so_far = max(max_so_far, current_max);

            // Kadane's algorithm for minimum subarray sum
            current_min = min(x, current_min + x);
            min_so_far = min(min_so_far, current_min);
        }

        // Handle the edge case where all numbers are negative.
        // In this case, max_so_far will hold the largest negative number (correct answer),
        // and total_sum - min_so_far would incorrectly be 0 because min_so_far == total_sum.
        if (max_so_far < 0) {
            return max_so_far;
        }

        // The result is the maximum of the non-circular max sum
        // and the circular max sum (total_sum - min_so_far).
        return max(max_so_far, total_sum - min_so_far);

    }
};

// 引入 INT_MIN

using namespace std;

class Solution {
public:
    int maxSubarraySumCircular(vector<int> &nums) {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }

        // 计算概念上 2n 长度数组的前缀和
        vector<long long> prefix_sum(2 * n + 1, 0); // 使用 long long 防止溢出
        for (int i = 0; i < 2 * n; ++i) {
            prefix_sum[i + 1] = prefix_sum[i] + nums[i % n];
        }

        // 单调队列，存储前缀和数组的下标
        deque<int> dq;
        int max_sum = numeric_limits<int>::min(); // 初始化为最小整数

        // 遍历前缀和数组（从 P[0] 开始）
        for (int i = 0; i <= 2 * n; ++i) {
            // 1. 移除队首过时下标 (保证窗口长度不超过 n)
            // 当前考虑的是 P[i], 窗口起点下标 j 必须满足 i - j <= n
            // 即 j >= i - n
            while (!dq.empty() && dq.front() < i - n) {
                dq.pop_front();
            }

            // 2. 计算以 nums[i-1] (在2n数组中) 结尾的最大和
            // 需要找到 P[j] 的最小值，其中 j 在 [max(0, i-n), i-1] 范围内
            // 由于队列单调性，队首 dq.front() 就是 P[j] 最小值的下标
            if (!dq.empty()) {
                // P[i] - P[dq.front()] 是长度 <= n 且结束于 i-1 的子数组和
                max_sum = max(max_sum, (int)(prefix_sum[i] - prefix_sum[dq.front()]));
            }

            // 3. 维护队尾单调性 (P[j] 单调递增)
            while (!dq.empty() && prefix_sum[dq.back()] >= prefix_sum[i]) {
                dq.pop_back();
            }

            // 4. 当前下标入队
            dq.push_back(i);
        }

        return max_sum;
    }
};