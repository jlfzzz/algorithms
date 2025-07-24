#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>
#include <queue>

using namespace std;

class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int oneCount = 0;
        for (int x : nums) {
            if (x) oneCount++;
        }

        int n = nums.size();
        if (oneCount == 0 || oneCount == n) return 0;

        int left = 0;
        int zeroCount = 0;
        
        int ans = n + 1;

        for (int right = 0;right < 2 * n; right++) {
            if (nums[right % n] == 0) zeroCount++;

            if (right - left + 1 == oneCount) {
                ans = min(ans, zeroCount);
                if (nums[left % n] == 0) zeroCount--;
                left++;
            }
        }
        return ans;
    }
};