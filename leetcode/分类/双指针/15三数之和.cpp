#include <vector>
#include <algorithm>

using namespace std;

/*
给你一个整数数组 nums ，判断是否存在三元组[nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，
同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

示例 1：

输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。
示例 2：

输入：nums = [0,1,1]
输出：[]
解释：唯一可能的三元组和不为 0 。
示例 3：

输入：nums = [0,0,0]
输出：[[0,0,0]]
解释：唯一可能的三元组和为 0 。
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        vector<vector<int>> res;
        int left;
        int right;

        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; ++i) {
            // 因为这是排序过的，所以nums[i]就是三个数中最小的，所以如果和上一个一样直接跳过

            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int current = nums[i];
            left = i + 1;
            right = nums.size() - 1;

            // 优化，最小的3个加起来大于0，后面的肯定都大于0
            if (nums[left] + nums[left + 1] + current > 0) {
                break;
            }

            // 同理，不过由于i在变大，所以是continue
            if (nums[right - 1] + nums[right] + current < 0) {
                continue;
            }


            while (left < right) {
                if (nums[left] + nums[right] + current == 0) {
                    vector<int> temp{ nums[left], nums[right], current };
                    // sort(temp.begin(), temp.end());
                    res.push_back(temp);

                    // 去重
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    // 跳过重复的right
                    while (left < right && nums[right] == nums[right - 1]) right--;

                    ++left;
                    --right;
                } else if (nums[left] + nums[right] + current < 0) {
                    ++left;
                } else {
                    --right;
                }
            }
        }

        //res.erase(unique(res.begin(), res.end()), res.end());
        return res;
    }
};