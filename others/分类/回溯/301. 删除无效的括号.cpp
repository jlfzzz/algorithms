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
    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;
        int max_len = 0;
        unordered_set<string> visited;  // 避免重复结果

        function<void(int, int, int, string &)> dfs =
            [&](int index, int open, int close, string &current) {
            // 剪枝：右括号多于左括号，或当前长度不可能超过max_len
            if (close > open || current.size() + (s.size() - index) < max_len) {
                return;
            }

            if (index == s.size()) {
                if (open == close) {
                    if (current.size() > max_len) {
                        ans.clear();
                        max_len = current.size();
                    }
                    if (current.size() == max_len && !visited.count(current)) {
                        ans.push_back(current);
                        visited.insert(current);
                    }
                }
                return;
            }

            char c = s[index];
            if (c != '(' && c != ')') {
                current.push_back(c);
                dfs(index + 1, open, close, current);
                current.pop_back();
                return;
            }

            // 不选当前括号
            dfs(index + 1, open, close, current);

            // 选当前括号
            current.push_back(c);
            if (c == '(') {
                dfs(index + 1, open + 1, close, current);
            } else {
                dfs(index + 1, open, close + 1, current);
            }
            current.pop_back();
            };

        string current;
        dfs(0, 0, 0, current);
        return ans;
    }
};