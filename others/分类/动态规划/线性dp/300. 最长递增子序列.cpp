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
    int lengthOfLIS(vector<int> &nums) {
        int n = nums.size();
        vector<int> f(n);
        for (int i = 0; i < n; i++) {
            f[i] = 0;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    f[i] = max(f[i], f[j]);
                }
            }
            f[i]++;
        }
        return ranges::max(f);
    }
};

class Solution {
public:
    int lengthOfLIS(vector<int> &nums) {
        int n = nums.size();
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            if (ranges::lower_bound(ans, x) == ans.end()) {
                ans.emplace_back(x);
            } else {
                *ranges::lower_bound(ans, x) = x;
            }
        }

        return ans.size();
    }
};