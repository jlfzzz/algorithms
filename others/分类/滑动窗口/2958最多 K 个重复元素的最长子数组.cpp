#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxSubarrayLength(vector<int> &nums, int k) {
        int n = nums.size();
        int l = 0, r = 0;
        unordered_map<int, int> winMap;
        int res = 0;

        while (r < n) {
            auto iter = winMap.find(nums[r]);
            if (iter != winMap.end()) {
                iter->second += 1;
            } else {
                winMap.emplace(nums[r], 1);
            }

            while (iter != winMap.end() && iter->second > k) {
                auto it = winMap.find(nums[l]);

                it->second -= 1;

                if (iter->second == 0) {
                    winMap.erase(iter);
                }

                ++l;
            }
            res = max(res, r - l + 1);
            ++r;
        }
        return res;
    }
};

class Solution2 {
public:
    int maxSubarrayLength(vector<int> &nums, int k) {
        unordered_map<int, int> freq;
        int left = 0;
        int ans = 0;

        for (int right = 0; right < nums.size(); ++right) {
            freq[nums[right]]++;

            // 当某个元素的频率超过 k 时，移动左指针
            while (freq[nums[right]] > k) {
                freq[nums[left]]--;
                left++;
            }

            // 更新最大长度
            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};