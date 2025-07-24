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
    int countLargestGroup(int n) {
        string s = to_string(n);
        int m = s.size();
        vector memo(m, vector<int>(m * 9 + 1, -1));
        auto dfs = [&](this auto &&dfs, int i, int left, bool limit_high) -> int {
            if (i == m) {
                return left == 0;
            }
            if (!limit_high && memo[i][left] != -1) {
                return memo[i][left];
            }

            int hi = limit_high ? s[i] - '0' : 9; // 当前数位至多填 hi
            int res = 0;
            for (int d = 0; d <= min(hi, left); d++) { // 枚举当前数位填 d
                res += dfs(i + 1, left - d, limit_high && d == hi);
            }

            if (!limit_high) {
                memo[i][left] = res;
            }
            return res;
            };

        int max_cnt = 0, ans = 0;
        for (int target = 1; target <= m * 9; target++) { // 枚举目标数位和
            int cnt = dfs(0, target, true);
            if (cnt > max_cnt) {
                max_cnt = cnt;
                ans = 1;
            } else if (cnt == max_cnt) {
                ans++;
            }
        }
        return ans;
    }
};

class Solution {
public:
    int countLargestGroup(int n) {
        unordered_map<int, int> mp;
        int ans = 0;
        int count = 0;
        for (int i = 1; i <= n; i++) {
            int sum = 0;
            int number = i;
            while (number > 0) {
                sum += number % 10;
                number /= 10;
            }
            mp[sum]++;
            if (mp[sum] > ans) {
                ans = mp[sum];
                count = 1;
            } else if (mp[sum] == ans) {
                count++;
            }
        }
        return count;
    }
};