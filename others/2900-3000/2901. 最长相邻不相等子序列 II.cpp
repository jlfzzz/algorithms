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
    vector<string> getWordsInLongestSubsequence(vector<string> &words, vector<int> &groups) {
        int n = words.size();
        vector<int> dp(n, 0);

        auto check = [&](string &s1, string &s2) -> bool {
            int count = 0;
            int m = s1.size();
            for (int i = 0; i < m; i++) {
                if (s1[i] != s2[i]) {
                    count++;
                    if (count > 1) {
                        return false;
                    }
                }
            }
            return count == 1 ? true : false;
            };

        int max_i = n - 1;
        vector<int> from(n, -1);

        for (int i = n - 1; i >= 0; i--) {
            from[i] = i;
            for (int j = i + 1; j < n; j++) {
                if (words[i].size() == words[j].size() && groups[i] != groups[j] && check(words[i], words[j])) {
                    if (dp[j] > dp[i]) {
                        dp[i] = dp[j];
                        from[i] = j;
                    }
                }
            }
            dp[i]++;
            if (dp[i] > dp[max_i]) {
                max_i = i;
            }
        }

        vector<string> ans;
        while (from[max_i] != max_i) {
            ans.emplace_back(words[max_i]);
            max_i = from[max_i];
        }
        ans.emplace_back(words[max_i]);//最后一个
        return ans;
    }
};