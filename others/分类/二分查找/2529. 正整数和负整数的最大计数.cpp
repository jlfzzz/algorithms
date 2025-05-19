#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int myLowerBound(vector<int> &nums, int target) {
        int left = -1;
        int right = nums.size();

        while (left + 1 < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] < target) {
                left = mid;
            } else {
                right = mid;
            }
        }

        return right;
    }

    int maximumCount(vector<int> &nums) {
        int posZero = myLowerBound(nums, 0);

        //if (posZero == nums.size() || nums[posZero] != 0) {}
        int posOne = myLowerBound(nums, 1);

        

        return max(posZero - 0, (int)nums.size() - posOne);
    }
    
    // int maximumCount(vector<int> &nums) {
    //     int posZero = lower_bound(nums.begin(), nums.end(), 0) - nums.begin();
    //     int posOne = lower_bound(nums.begin(), nums.end(), 1) - nums.begin();

    //     return max(posZero - 0, (int) nums.size() - posOne);
    // }
};