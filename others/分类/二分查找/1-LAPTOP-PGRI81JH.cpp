#include <algorithm>
#include <ranges>
#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size();
        int comp = nums[right - 1];
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < comp) {
                right = mid;
            } else {
                left = mid + 1; 
            }
        }
        return right == nums.size() ? nums[0] : nums[right]; 
    }
};