#include <algorithm>
#include <ranges>
#include <vector>

using namespace std;

class Solution {
public:
    bool check(vector<int> &nums, int k) {
        long long extra = 0;
        for (int i : nums) {
            if (i <= k) {
                extra += k - i;
            } else {
                if (i - k > extra) {
                    return false;
                } else {
                    extra -= (i - k);
                }
            }
        }
        return true;
    }

    int minimizeArrayValue(vector<int> &nums) {
        int right = *ranges::max_element(nums) + 1;
        int left = 0;
        int ans = 0;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (check(nums, mid)) {
                right = mid;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }
};

/*
class Solution {
public:
    bool check(vector<int>& nums, int maxN) {
        long long put = 0;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if (nums[i] < maxN) {
                put += (static_cast<long long>(maxN) - nums[i]);
            } else {
                if (nums[i] - maxN > put) {
                    return false;
                } else {
                    put -= (nums[i] - maxN);
                }
            }
        }
        return true;
    }

    int minimizeArrayValue(vector<int>& nums) {
        int maxN = *ranges::max_element(nums) + 1;
        int ans = maxN - 1;
        int left = 0;

        while (left < maxN) {
            int mid = left + (maxN - left) / 2;

            if (check(nums, mid)) {
                ans = mid;
                maxN = mid;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }
};
*/

