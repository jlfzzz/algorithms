#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string s;
        auto dfs = [&](this auto&&dfs, int open, int close) ->void {
            if (s.size() == 2 * n) {
                ans.push_back(s);
                return;
            }

            // 迭代添加 '('
            if (open < n) {
                s += '(';
                dfs(open + 1, close);
                s.pop_back();
            }

            // 迭代添加 ')'
            if (close < open) {
                s += ')';
                dfs(open, close + 1);
                s.pop_back();
            }
            };
        dfs(0, 0);
        return ans;
    }
};