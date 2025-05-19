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
#include <stack>
#include <set>
#include <random>

using namespace std;

class Solution {
public:
    int maximumUniqueSubarray(vector<int> &nums) {
        unordered_map<int, int> window;
        int left = 0;
        int ans = 0;
        int sum = 0;
        for (int right = 0; right < nums.size(); right++) {
            window[nums[right]]++;
            sum += nums[right];
            while (window[nums[right]] > 1) {
                window[nums[left]]--;
                sum -= nums[left];
                left++;
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};