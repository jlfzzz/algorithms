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

using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int> &nums, int k) {
        double ans = -100000000;
        int left = 0;
        int n = nums.size();
        double sum = 0;
        for (int right = 0; right < n; right++) {
            sum += nums[right];

            if (right - left + 1 == k) {
                ans = max(ans, sum / k);
                sum -= nums[left];
                left++;
            }
        }
        return ans;
    }
};