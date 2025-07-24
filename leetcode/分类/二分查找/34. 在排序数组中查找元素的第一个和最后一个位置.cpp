#include <vector>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int> &nums, int target) {
        if (nums.empty()) return { -1, -1 };

        int n = nums.size();
        auto lowerBound = [&](int target) {
            int left = 0;
            int right = n;

            while (left < right) {
                int mid = left + (right - left) / 2;
                if (nums[mid] < target) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            return left;
            };

        int lower = lowerBound(target);
        int upper = lowerBound(target + 1) - 1;

        if (lower >= n || nums[lower] != target) {
            return { -1, -1 };
        } else {
            return { lower, upper };
        }
    }
};