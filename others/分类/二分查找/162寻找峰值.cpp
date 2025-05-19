#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = -1;
        int right = nums.size();
        int ans = 0;
        int n = nums.size();

        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (mid == n - 1) {
                right = mid;
                continue;
            }
            
            if (nums[mid] > nums[mid + 1]) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return right;
        // int l = 0, r = nums.size() - 1, m;
        // while (l < r) {
        //     m = l + (r - l) / 2;
        //     if (nums[m] > nums[m + 1]) {
        //         r = m;
        //     } else {
        //         l = m + 1;
        //     }
        // }
        // return l;
    }
};