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
    int countSubarrays(vector<int> &nums) {
        int ans = 0;
        for (int i = 2; i < nums.size(); i++) {
            if ((nums[i - 2] + nums[i]) * 2 == nums[i - 1]) {
                ans++;
            }
        }
        return ans;
    }
};