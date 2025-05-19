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

    vector<int> successfulPairs(vector<int> &spells, vector<int> &potions, long long success) {
        vector<int> ans;
        int n = potions.size();

        sort(potions.begin(), potions.end());
        for (long long i : spells) {
            auto target = (success + i - 1) / i;
            int x = myLowerBound(potions, target);
            ans.emplace_back(n - x);
        }

        return ans;
    }

    
};

