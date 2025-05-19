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
    int minimizeTheDifference(vector<vector<int>> &mat, int target) {
        vector<int> dp(target * 2 + 1);
        int n = mat.size();
        int m = mat[0].size();
        dp[0] = 1;
        int min_sum = 0;

        for (int i = 0; i < n; i++) {
            min_sum += *min_element(mat[i].begin(), mat[i].end());

            vector<int> temp(target * 2 + 1);
            for (int j = 0; j < m; j++) {
                int x = mat[i][j];
                for (int k = max(x, min_sum); k <= 2 * target; k++) {
                    temp[k] = temp[k] || dp[k - x];
                }
            }
            swap(temp, dp);
        }

        int ans = 1e9;
        ans = min(ans, abs(min_sum - target));
        for (int i = min_sum; i <= 2 * target; i++) {
            if (dp[i]) {
                ans = min(ans, abs(i - target));
            }
        }
        return ans;
    }
};