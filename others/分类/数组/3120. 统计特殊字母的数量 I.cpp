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

class Solution {
public:
    int numberOfSpecialChars(string word) {
        unordered_map<char, pair<bool, bool>> m;
        int ans = 0;

        for (char c : word) {
            if (c >= 'a' && c <= 'z') {
                m[c].first = true;  // 标记该小写字母出现
            } else if (c >= 'A' && c <= 'Z') {
                // 转换大写为对应的小写，标记为大写出现
                m[c + 32].second = true;
            }
        }

        for (auto &p : m) {
            if (p.second.first && p.second.second)
                ans++;
        }
        return ans;
    }
};
