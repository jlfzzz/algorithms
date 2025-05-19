#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>

using namespace std;


// 方法二从后向前
class Solution {
public:
    int minimumOperations(vector<int> &nums) {
        int n = nums.size();
        int ans = 0;
        int left = 0;
        unordered_map<int, int> map;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            map[x]++;


            while (i - left >= 3 && map[x] > 1) {
                for (int j = 0; j < 3; j++) {
                    if (map[nums[left]] > 0) {
                        map[nums[left]]--;
                    }
                    left++;
                }
                ans++;
            }
        }

        for (; left < n; left++) {
            if (map[nums[left]] > 1) {
                ans++;
                break;
            }
        }

        return ans;
    }
};

class Solution {
public:
    int minimumOperations(vector<int> &nums) {
        unordered_set<int> seen;
        for (int i = nums.size() - 1; i >= 0; i--) {
            if (!seen.insert(nums[i]).second) { // nums[i] 在 seen 中
                return i / 3 + 1;
            }
        }
        return 0;
    }
};
