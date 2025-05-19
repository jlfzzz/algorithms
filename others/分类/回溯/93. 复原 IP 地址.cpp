#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <unordered_set>

using namespace std;

//dfs and bfs

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        unordered_set<string> result_set; // 改用集合存储结果，自动去重
        int left_remove = 0, right_remove = 0;

        // 计算最少需要删除的左右括号数
        for (char c : s) {
            if (c == '(') left_remove++;
            else if (c == ')') {
                if (left_remove > 0) left_remove--;
                else right_remove++;
            }
        }

        function<void(int, int, int, int, int, string &)> dfs =
            [&](int index, int left, int right, int left_rem, int right_rem, string &path) {
            if (index == s.size()) {
                if (left == right && left_rem == 0 && right_rem == 0) {
                    result_set.insert(path); // 插入集合，自动去重
                }
                return;
            }

            char c = s[index];
            // 情况1：删除当前字符（如果是括号）
            if ((c == '(' && left_rem > 0) || (c == ')' && right_rem > 0)) {
                dfs(index + 1, left, right,
                    left_rem - (c == '('), right_rem - (c == ')'), path);
            }

            // 情况2：保留当前字符
            path.push_back(c);
            if (c != '(' && c != ')') {
                dfs(index + 1, left, right, left_rem, right_rem, path);
            } else if (c == '(') {
                dfs(index + 1, left + 1, right, left_rem, right_rem, path);
            } else if (right < left) {
                dfs(index + 1, left, right + 1, left_rem, right_rem, path);
            }
            path.pop_back();
            };

        string path;
        dfs(0, 0, 0, left_remove, right_remove, path);

        // 将集合转为 vector 返回
        return vector<string>(result_set.begin(), result_set.end());
    }
};

class Solution2 {
public:
    vector<string> res;
    vector<string> removeInvalidParentheses(string s) {
        int leftnum = 0;
        int rightnum = 0;
        for (char a : s) {
            if (a == '(') {
                leftnum++;
            }
            if (a == ')' && leftnum > 0) {
                leftnum--;
            } else if (a == ')' && leftnum == 0)
                rightnum++;
        }
        helper(s, 0, leftnum, rightnum);
        return res;
    }

    void helper(string s, int start, int leftnum, int rightnum) {
        if (leftnum == 0 && rightnum == 0) {
            if (isvalid(s))
                res.push_back(s);
        }

        for (int i = start;i < s.size();i++) {
            if (leftnum + rightnum > s.size() - i)
                return;
            if (i != start && s[i] == s[i - 1])
                continue;

            if (leftnum > 0 && s[i] == '(')
                helper(s.substr(0, i) + s.substr(i + 1), i, leftnum - 1, rightnum);
            if (rightnum > 0 && s[i] == ')')
                helper(s.substr(0, i) + s.substr(i + 1), i, leftnum, rightnum - 1);
        }
    }
    bool isvalid(string s) {
        int left = 0;
        for (char a : s) {
            if (a == '(')
                left++;
            if (a == ')') {
                left--;
                if (left < 0) return false;
            }
        }
        return left == 0;
    }
};