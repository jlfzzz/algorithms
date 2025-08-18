class Solution {
public:
    long long perfectPairs(vector<int> &nums) {
        for (int &x: nums) {
            x = abs(x);
        }

        ranges::sort(nums);
        long long ans = 0;
        int left = 0;
        for (int j = 0; j < nums.size(); j++) {
            int b = nums[j];
            while (nums[left] * 2 < b) {
                left++;
            }
            ans += j - left;
        }
        return ans;
    }
};
