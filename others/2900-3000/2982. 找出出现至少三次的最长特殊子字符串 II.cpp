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
    int maximumLength(string s) {
        vector<vector<int>> record(26);
        int n = s.size();

        // 处理第一个字符
        char curr = s[0];
        int count = 1;

        // 处理字符串中的连续字符
        for (int i = 1; i < n; i++) {
            if (s[i] == curr) {
                count++;
            } else {
                record[curr - 'a'].push_back(count);
                curr = s[i];
                count = 1;
            }
        }
        // 处理最后一组连续字符
        record[curr - 'a'].push_back(count);

        int ans = -1;
        for (int i = 0; i < 26; i++) {
            if (record[i].empty()) continue;

            // 获取当前字符的最大连续长度
            int maxLen = *max_element(record[i].begin(), record[i].end());

            // 二分查找满足条件的最大长度
            int lo = 1, hi = maxLen + 1;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;

                // 计算长度为mid的子串出现次数
                int validCount = 0;
                for (int len : record[i]) {
                    validCount += max(0, len - mid + 1);
                }

                if (validCount >= 3) {
                    // 如果找到至少3个子串，尝试更大的长度
                    lo = mid + 1;
                    ans = max(ans, mid);
                } else {
                    // 否则尝试更小的长度
                    hi = mid;
                }
            }
        }

        return ans;
    }
};