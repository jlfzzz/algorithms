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
#include <stack>
#include <set>
#include <random>

using namespace std;

// 倒着想的滑窗和前后缀处理

class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        int left = 0;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int target = sum - x;
        int max_window = -1;
        int curr = 0;
        for (int right = 0; right < n; right++) {
            curr += nums[right];
            while (left < n && curr > target) {
                curr -= nums[left];
                left++;
            }
            if (curr == target) {
                max_window = max(max_window, right - left + 1);
            }
        }
        if (max_window == -1) {
            return -1;
        } else {
            return n - max_window;
        }
    }
};
class Solution {
public:
    int minOperations(vector<int> &nums, int x) {
        int n = nums.size();
        int left = 0;
        int right = n;
        int curr = 0;
        int ans = n + 1;

        // 初始化 curr 为前缀和
        while (left < n && curr < x) {
            curr += nums[left];
            left++;
        }
        if (curr == x) ans = left;

        // 开始滑动窗口，将右侧元素加入 curr，同时移除左侧元素维持窗口
        while (left > 0) {
            left--;
            curr -= nums[left];
            while (right > left && curr < x) {
                right--;
                curr += nums[right];
            }
            if (curr == x) {
                ans = min(ans, left + (n - right));
            }
        }

        return (ans <= n) ? ans : -1;
    }
};
    