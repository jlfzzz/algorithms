/*
给定一个包含非负整数的数组 nums ，返回其中可以组成三角形三条边的三元组个数。
示例 1:

输入: nums = [2,2,3,4]
输出: 3
解释:有效的组合是:
2,3,4 (使用第一个 2)
2,3,4 (使用第二个 2)
2,2,3
示例 2:

输入: nums = [4,2,3,4]
输出: 4
*/


#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
public:
    int triangleNumber(vector<int> &nums) {
        int n = nums.size();
        if (n < 3) {
            return 0;
        }
        int count = 0;

        ranges::sort(nums);
        for (int i = 0; i < n - 2; i++) {
            if (nums[i] == 0) {
                continue;
            }
            int left = i + 1;
            int right = left + 1;

            while (left < n - 1) {
                while (right < n && (nums[i] + nums[left] > nums[right])) {
                    right++;
                }
                count += right - left - 1;
                left++;
            }
        }
        return count;
    }
};


/*
int res = 0;
        int n = nums.size();
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; ++i) {
            if (nums[i] == 0) {
                continue;
            }

            int left = i + 1;
            int right = i + 2;

            for (; left < n - 1; ++left) {

                主要是第三条边，也就是最长边在进行双指针递增时候，我们更新了left（第二条边），但不用去重置right（第三条边），因为最后更新结果是两个索引相减，因为数组排好序了，等于已经默认这个差值里面的都能构成三角形。所以最后是n ^ 2，如果你重置了right（第三条边），就是n ^ 3



while (right < n && nums[i] + nums[left] > nums[right]) {
    ++right;
}

res += right - left - 1;
            }
        }
        return res;
*/

