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
    int minAbsoluteSumDiff(vector<int> &nums1, vector<int> &nums2) {
        vector<int> rec(nums1);
        ranges::sort(rec);
        int mod = 1000000007;

        int n = nums1.size();
        int sum = 0;
        int offset = 0;
        for (int i = 0; i < n; i++) {
            int diff = abs(nums1[i] - nums2[i]);
            sum = (sum + diff) % mod;

            int j = lower_bound(rec.begin(), rec.end(), nums2[i]) - rec.begin();
            if (j == n) {
                j--;
            }

            int newDiff = abs(rec[j] - nums2[i]);
            if (j > 0) {
                newDiff = min(newDiff, abs(rec[j - 1] - nums2[i]));
            }

            offset = max(offset, abs(diff - newDiff));
        }

        return (sum - offset + mod) % mod;
    }
};