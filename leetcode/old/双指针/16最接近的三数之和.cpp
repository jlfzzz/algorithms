/*
给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums 中选出三个整数，使它们的和与 target 最接近。

返回这三个数的和。

假定每组输入只存在恰好一个解。



示例 1：

输入：nums = [-1,2,1,-4], target = 1
输出：2
解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2)。
示例 2：

输入：nums = [0,0,0], target = 1
输出：0
解释：与 target 最接近的和是 0（0 + 0 + 0 = 0）。
*/

#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int> &nums, int target) {
        int ans = 99999999;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() - 2; ++i) {
            int left = i + 1;
            int right = nums.size() - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                int diff = abs(target - sum);
                int ansDiff = abs(target - ans);

                if (sum == target) {
                    return target;
                }

                ans = diff < ansDiff ? sum : ans;

                if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        return ans;
    }

};













/*
sort(nums.begin(), nums.end());

        //int res = INT_MAX;
        int res = 999999; //不能INT_MAX因为下面res - target如果target是负数会overflow
        int left;
        int right;

        for (int i = 0; i < nums.size() - 2; ++i) {
            int current = nums[i];
            left = i + 1;
            right = nums.size() - 1;

            while (left < right) {
                int sum = nums[left] + nums[right] + current;
                res = abs(sum - target) >= abs(res - target) ? res : sum;

                if (nums[left] + nums[right] + current == target) {
                    return target;
                } else if (nums[left] + nums[right] + current < target) {
                    ++left;
                } else {
                    --right;
                }
            }
        }

        return res;
        */