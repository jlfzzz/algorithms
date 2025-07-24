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
    int longestOnes(vector<int> &nums, int k) {
        int n = nums.size();
        int left = 0;
        int used = 0;
        int ans = 0;
        for (int right = 0; right < n; right++) {
            if (nums[right] == 0) {
                used++;
            }
            while (used > k) {
                if (nums[left] == 0) {
                    used--;
                }
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};