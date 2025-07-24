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

// O(1) space

class Solution {
public:
    vector<int> buildArray(vector<int> &nums) {
        int n = nums.size();
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = nums[nums[i]];
        }

        return ans;
    }
};

class Solution {
public:
    vector<int> buildArray(vector<int> &nums) {
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];
            if (x < 0) { // 已搬家
                continue;
            }
            int cur = i;
            while (nums[cur] != i) {
                int nxt = nums[cur];
                nums[cur] = ~nums[nxt]; // 把下一个数搬过来，同时做标记（取反）
                cur = nxt;
            }
            nums[cur] = ~x; // 对于这一组的最后一个数，把起点 x=nums[i] 搬过来
        }

        for (int i = 0; i < nums.size(); i++) {
            nums[i] = ~nums[i]; // 复原
        }
        return nums;
    }
};