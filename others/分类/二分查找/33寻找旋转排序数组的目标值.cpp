#include <algorithm>
#include <ranges>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int> &nums, int target) {
        int n = nums.size();
        int comp = nums[0];
        int left = 0;
        int right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= comp) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        int pos = left == n ? 0 : left;
        int ans;
        if (pos == 0) {
            ans = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
            //return nums[ans] == target ? ans : -1;
        } else {
            if (target >= comp) {
                ans = lower_bound(nums.begin(), nums.begin() + pos, target) - nums.begin();
            } else {
                ans = lower_bound(nums.begin() + pos, nums.end(), target) - nums.begin();
            }
        }
        if (ans == n || nums[ans] != target) {
            return -1;
        }
        return ans;
    }
};

class Solution2 {
public:
    int search(vector<int> &nums, int target) {
        int minPos = findMin(nums);

        if (nums[minPos] > target) {
            return -1;
        }


        if (minPos == 0) {
            return *lower_bound(nums.begin(), nums.end(), target);
        } else {
            if (target >= nums[0]) {
                return *lower_bound(nums.begin(), nums.begin() + minPos, target);
            } else {
                return *lower_bound(nums.begin() + minPos, nums.end(), target);
            }
        }
    }

    int findMin(vector<int> &nums) {
        int n = nums.size();
        int right = n;
        int left = -1;
        int comp = nums[0];

        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= comp) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return left != n - 1 ? right : 0; 
    }
};