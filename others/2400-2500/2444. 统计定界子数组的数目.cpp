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

using namespace std;

class Solution {
public:
    long long countSubarrays(vector<int> &nums, int minK, int maxK) {
        int n = nums.size();
        int min_pos = -1, max_pos = -1, out_of_bound_pos = -1;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int x = nums[i];
            if (x == minK) {
                min_pos = i;
            }

            if (x == maxK) {
                max_pos = i;
            }

            if (x < minK || x > maxK) {
                out_of_bound_pos = i;
            }

            ans += max(min(min_pos, max_pos) - out_of_bound_pos, 0);
        }

        return ans;
    }
};