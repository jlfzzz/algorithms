#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <ranges>
#include <numeric>

using namespace std;

// 一人一句： 逆向思维牛逼，来。
class Solution {
public:
    int minOperations(vector<int> &nums, int x) {
        int target = reduce(nums.begin(), nums.end()) - x;
        if (target < 0) {
            return -1; // 全部移除也无法满足要求
        }

        int ans = -1, left = 0, sum = 0, n = nums.size();
        for (int right = 0; right < n; right++) {
            sum += nums[right];
            while (sum > target) {
                sum -= nums[left];
                left++; // 缩小子数组长度
            }
            if (sum == target) {
                ans = max(ans, right - left + 1);
            }
        }
        return ans < 0 ? -1 : n - ans;
    }
};
