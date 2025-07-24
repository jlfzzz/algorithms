#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> ans;
    unordered_map<char, string> map;
    int n;

    vector<string> letterCombinations(string digits) {
        map['2'] = "abc";
        map['3'] = "def";
        map['4'] = "ghi";
        map['5'] = "jkl";
        map['6'] = "mno";
        map['7'] = "pqrs";
        map['8'] = "tuv";
        map['9'] = "wxyz";
        n = digits.size();
        dfs(0, digits, "");
        return ans;
    }

    void dfs(int index, string digits, string comb) {
        if (index == n) {
            if (comb.size())
                ans.emplace_back(comb);
            return;
        }

        auto all = map[digits[index]];
        for (auto &opt : all) {
            dfs(index + 1, digits, comb + opt);
        }
    }
};