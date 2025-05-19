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
    int maximumsSplicedArray(vector<int> &nums1, vector<int> &nums2) {
        return max(helper(nums1, nums2), helper(nums2, nums1));
    }

    int helper(vector<int> &nums1, vector<int> &nums2) {
        int n = nums1.size();

        int totalSum = 0;
        int diffMax = 0;
        int diff = 0;
        for (int i = 0; i < n; i++) {
            totalSum += nums1[i];

            diff = max(diff + nums2[i] - nums1[i], nums2[i] - nums1[i]);
            diffMax = max(diffMax, diff);
        }

        return totalSum + diffMax;
    }
};