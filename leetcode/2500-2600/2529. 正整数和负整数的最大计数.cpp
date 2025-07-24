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
    int maximumCount(vector<int> &nums) {
        auto zeroPos = lower_bound(nums.begin(), nums.end(), 0);
        auto onePos = upper_bound(nums.begin(), nums.end(), 0);
        return max(zeroPos - nums.begin(), nums.end() - onePos);
    }
};