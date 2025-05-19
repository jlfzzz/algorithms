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
    int maxDotProduct(vector<int> &nums1, vector<int> &nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        vector<vector<int>> f(n1 + 1, vector<int>(n2 + 1, -1e8));
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                int tmp = nums1[i - 1] * nums2[j - 1];
                f[i][j] = max({ f[i][j - 1], f[i - 1][j], f[i - 1][j - 1] + tmp, tmp });
            }
        }
        return f[n1][n2];
    }
};