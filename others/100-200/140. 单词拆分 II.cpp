#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };


class Solution {
public:
    vector<string> wordBreak(string s, vector<string> &wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        int n = s.length();
        vector<string> ans;

        // 找到字典中最长单词的长度
        int maxLen = 0;
        for (const string &word : wordDict) {
            maxLen = max(maxLen, (int)word.length());
        }

        vector<string> path;
        dfs(s, 0, n, wordSet, maxLen, path, ans);
        return ans;
    }

    void dfs(const string &s, int i, int n, const unordered_set<string> &wordSet,
        int maxLen, vector<string> &path, vector<string> &ans) {
        if (i == n) {
            // 将路径中的单词用空格连接
            string result = "";
            for (int j = 0; j < path.size(); j++) {
                if (j > 0) result += " ";
                result += path[j];
            }
            ans.push_back(result);
            return;
        }

        // 尝试所有可能的单词长度
        for (int k = 1; k <= min(maxLen, n - i); k++) {
            string word = s.substr(i, k);
            if (wordSet.find(word) != wordSet.end()) {
                path.push_back(word);
                dfs(s, i + k, n, wordSet, maxLen, path, ans);
                path.pop_back();
            }
        }
    }
};