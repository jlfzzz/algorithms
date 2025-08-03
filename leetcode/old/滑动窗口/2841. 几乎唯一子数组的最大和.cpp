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
    long long maxSum(vector<int> &nums, int m, int k) {
        long long ans = 0;
        int n = nums.size();
        int left = 0;
        int count = 0;
        int different = 0;
        long long sum = 0;
        unordered_map<int, int> map;
        for (int right = 0; right < n; right++) {
            int x = nums[right];
            sum += x;
            if (map[x] == 0) different++;
            map[x]++;
            if (right - left + 1 == k) {
                if (different >= m) ans = max(ans, sum);
                map[nums[left]]--;
                sum -= nums[left];
                if (map[nums[left]] == 0) different--;
                left++;
            }
        }
        return ans;
    }
};

// 为0了erase掉剩空间
class Solution {
public:
    long long maxSum(vector<int> &nums, int m, int k) {
        long long ans = 0, s = 0;
        unordered_map<int, int> cnt;
        for (int i = 0; i < nums.size(); i++) {
            // 1. 进入窗口
            s += nums[i];
            cnt[nums[i]]++;

            int left = i - k + 1;
            if (left < 0) { // 窗口大小不足 k
                continue;
            }

            // 2. 更新答案
            if (cnt.size() >= m) {
                ans = max(ans, s);
            }

            // 3. 离开窗口
            int out = nums[left];
            s -= out;
            if (--cnt[out] == 0) {
                cnt.erase(out);
            }
        }

        return ans;
    }
};