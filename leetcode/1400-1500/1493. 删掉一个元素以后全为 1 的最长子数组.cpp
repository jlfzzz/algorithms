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

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int> &nums) {
        int n = nums.size();
        int ans = 0;
        int left = 0;
        int zeroCount = 0; // 记录当前窗口中0的个数

        for (int right = 0; right < n; right++) {
            if (nums[right] == 0) {
                zeroCount++;
            }

            // 如果窗口中0的个数超过1，移动左指针直到删除一个0
            while (zeroCount > 1) {
                if (nums[left] == 0) {
                    zeroCount--;
                }
                left++;
            }

            // 计算当前窗口长度（需要减1，因为要删除一个元素）
            ans = max(ans, right - left);
        }

        return min(ans, n - 1); // 确保结果不超过n-1（至少删除一个元素）
    }
};