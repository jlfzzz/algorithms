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
    long long countSubarrays(vector<int> &nums, long long k) {
        long long sum = 0;
        long long ans = 0;
        int n = nums.size();
        int left = 0;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            while (left <= i && sum * (i - left + 1) >= k) {
                sum -= nums[left];
                left++;
            }
            ans += i - left + 1;
        }
        return ans;
    }
};