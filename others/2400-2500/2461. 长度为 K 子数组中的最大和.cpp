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
#include <bitset>

using namespace std;

class Solution {
public:
    long long maximumSubarraySum(vector<int> &nums, int k) {
        unordered_map<int, int> map;
        long long ans = 0;
        long long sum = 0;
        int count = 0;
        int left = 0;
        int n = nums.size();

        for (int right = 0; right < n; right++) {
            int i = nums[right];
            map[i]++;
            sum += i;
            count++;
            if (map[i] > 1) {
                while (nums[left] != i) {
                    map[nums[left]]--;
                    if (map[nums[left]] == 0)
                        map.erase(nums[left]);
                    sum -= nums[left];
                    left++;
                    count--;
                }
                map[i]--;
                sum -= i;
                left++;
                count--;
            }

            while (count > k) {
                map[nums[left]]--;
                if (map[nums[left]] == 0)
                    map.erase(nums[left]);
                sum -= nums[left];
                left++;
                count--;
            }

            if (count == k)
                ans = max(ans, sum);
        }
        return ans;
    }
};