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

using namespace std;

class Solution {
public:
    int minZeroArray(vector<int> &nums, vector<vector<int>> &queries) {
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) { // 每个 nums[i] 单独计算 0-1 背包
            int x = nums[i];
            if (x == 0) {
                continue;
            }
            vector<int> f(x + 1);
            f[0] = true;
            for (int k = 0; k < queries.size(); k++) {
                auto &q = queries[k];
                if (i < q[0] || i > q[1]) {
                    continue;
                }
                int val = q[2];
                for (int j = x; j >= val; j--) {
                    f[j] = f[j] || f[j - val];
                }
                if (f[x]) { // 满足要求
                    ans = max(ans, k + 1);
                    break;
                }
            }
            if (!f[x]) { // 所有操作都执行完了也无法满足
                return -1;
            }
        }
        return ans;
    }
};