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
    int countCompleteSubarrays(vector<int> &nums) {
        int n = nums.size();
        unordered_map<int, int> mp;
        for (int x : nums) mp[x]++;

        int diffNumbers = mp.size();
        unordered_map<int, int> record;
        int left = 0;
        int ans = 0;
        for (int right = 0; right < n; right++) {
            int number = nums[right];
            record[number]++;

            while (record.size() == diffNumbers) {
                ans += n - right;
                record[nums[left]]--;
                if (record[nums[left]] == 0) {
                    record.erase(nums[left]);
                }
                left++;
            }
        }
        return ans;
    }
};