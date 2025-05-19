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
#include <limits> 

using namespace std;

class Solution {
public:
    int maxProduct(vector<int> &nums) {
        int ans = INT_MIN; // 注意答案可能是负数
        int f_max = 1, f_min = 1;
        for (int x : nums) {
            int mx = f_max;
            f_max = max({ f_max * x, f_min * x, x });
            f_min = min({ mx * x, f_min * x, x });
            ans = max(ans, f_max);
        }
        return ans;
    }
};

class Solution {
public:
    int maxProduct(vector<int> &nums) {
        int n = nums.size();
        int ans = nums[0];
        int negMax = 1;
        int posMax = 1;

        for (int i = 0; i < n; i++) {
            int temp = posMax;

            posMax = max({ posMax * nums[i], nums[i], negMax * nums[i] });
            negMax = min({ temp * nums[i], nums[i], negMax * nums[i] });

            ans = max(ans, posMax);
        }

        return ans;
    }
};