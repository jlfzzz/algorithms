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
#include <cstring>
#include <array> 
#include <bitset>

using namespace std;

class Solution {
public:
    int smallestDivisor(vector<int> &nums, int threshold) {
        int mx = *max_element(nums.begin(), nums.end()) + 1;
        int mn = 1;
        int n = nums.size();
        int ans = mx - 1;

        while (mn < mx) {
            int mid = mn + (mx - mn) / 2;

            int sum = 0;
            for (int i = 0; i < n; i++) {
                sum += (nums[i] + mid - 1) / mid;
            }

            if (sum > threshold) {
                mn = mid + 1;
            } else {
                ans = min(ans, mid);
                mx = mid;
            }
        }

        return ans;
    }
};