#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    long long countFairPairs(vector<int> &nums, int lower, int upper) {
        long long ans = 0;

        ranges::sort(nums);

        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int current = nums[i];
            auto lowerB = lower_bound(nums.begin() + i + 1, nums.end(), lower - current);
            auto higherB = lower_bound(nums.begin() + i + 1, nums.end(), upper - current + 1);
            ans += higherB - lowerB;
        }

        return ans;
    }
};