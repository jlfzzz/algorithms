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
    void nextPermutation(vector<int> &nums) {
        int n = nums.size();
        if (n <= 1) {
            return; // 长度为 0 或 1 的数组没有下一个排列
        }

        // 1. 从右向左查找第一个满足 nums[i] < nums[i+1] 的位置 i
        //    这个 nums[i] 就是需要被替换的“较小数”
        int i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        // 如果找到了这样的 i (i >= 0)
        if (i >= 0) {
            // 2. 从右向左查找第一个满足 nums[j] > nums[i] 的位置 j
            //    这个 nums[j] 就是用来替换 nums[i] 的“较大数”中最小的那个
            int j = n - 1;
            while (j > i && nums[j] <= nums[i]) {
                j--;
            }
            // 3. 交换 nums[i] 和 nums[j]
            swap(nums[i], nums[j]);
        }

        // 4. 将 i 位置之后的部分（包括 i 本身，如果 i < 0）反转
        //    如果 i < 0，说明整个数组是降序的，直接反转得到最小排列
        //    如果 i >= 0，反转 i+1 到末尾的部分，使得 i 之后的部分变为升序，
        //    这样在替换了 nums[i] 后得到的就是紧邻的下一个排列
        reverse(nums.begin() + i + 1, nums.end());
    }
};