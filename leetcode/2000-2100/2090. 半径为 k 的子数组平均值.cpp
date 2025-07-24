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
    vector<int> getAverages(vector<int> &nums, int k) {
        int n = nums.size();
        vector<int> ans(n, -1);
        int left = 0;
        int mid = k;
        int right = 2 * k;
        if (right >= n) {
            return ans;
        }
        long long sum = 0;
        for (int i = 0; i <= right; i++) {
            sum += nums[i];
        }
        for (; mid < n - k; mid++) {
            ans[mid] = sum / (2 * k + 1);
            sum -= nums[left];
            left++;
            right++;
            if (right < n)
                sum += nums[right];
        }
        return ans;
    }
};