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

using namespace std;

class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, n + 10000);
        dp[0] = 0;
        for (int i = 1; i <= sqrt(n); i++) {
            for (int j = 0; j <= n; j++) {
                if (j + i * i <= n) {
                    dp[j + i * i] = min(dp[j + i * i], dp[j] + 1);
                }
            }
        }
        return dp[n];
    }
};