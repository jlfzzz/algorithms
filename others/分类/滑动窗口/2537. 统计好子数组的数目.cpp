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
    long long countGood(vector<int> &nums, int k) {
        long long ans = 0;
        int left = 0;
        int n = nums.size();
        unordered_map<int, int> mp;
        int pairCount = 0;

        for (int right = 0; right < n; right++) {
            int x = nums[right];
            mp[x]++;
            if (mp[x] >= 2) pairCount += mp[x] - 1;

            while (pairCount >= k) {
                ans += n - right;
                pairCount -= (mp[nums[left]] - 1);
                mp[nums[left]]--;
                //if (mp[nums[left]] == 0)
                left++;
            }
        }

        return ans;
    }
};