#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};


class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = s.size(), m = words.size();
        if (m == 0) return {};
        int len = words[0].size();
        int totalLen = m * len;
        if (n < totalLen) return {};

        unordered_map<string, int> wordCount;
        for (const auto& word : words) {
            wordCount[word]++;
        }

        vector<int> result;
        for (int i = 0; i < len; ++i) {
            unordered_map<string, int> window;
            int left = i, count = 0;

            for (int right = i; right + len <= n; right += len) {
                string word = s.substr(right, len);
                if (wordCount.count(word)) {
                    window[word]++;
                    count++;

                    while (window[word] > wordCount[word]) {
                        string leftWord = s.substr(left, len);
                        window[leftWord]--;
                        left += len;
                        count--;
                    }

                    if (count == m) {
                        result.push_back(left);
                    }
                } else {
                    window.clear();
                    count = 0;
                    left = right + len;
                }
            }
        }

        return result;
    }
};



class Solution {
public:
    vector<int> findSubstring(string s, vector<string> &words) {
        int n = s.size();
        int len = words[0].size();
        int n_words = words.size();
        unordered_map<string, int> mp;
        for (string &ss : words) {
            mp[ss]++;
        }

        vector<int> ans;
        for (int i = 0; i < len; ++i) {
            unordered_map<string, int> window;
            int left = i; // left 初始化为当前偏移量

            // 内层循环：基于当前偏移量 i 进行滑动窗口
            // 结束条件优化：right 最多只需要到 n - len
            for (int right = i; right <= n - len; right += len) {
                string ss = s.substr(right, len);

                // --- 以下是你原来的内部逻辑，保持不变 ---
                // 注意：这里的 !mp[ss] 仍然会修改 mp，这是你原代码的行为
                // 同样，window[ss] 也会在 key 不存在时插入新元素
                if (!mp.count(ss)) { // 稍微修正：用 count 检查存在性，避免修改 mp
                    left = right + len;
                    window.clear();
                    continue;
                }

                // window[ss]++; // 将自增移到 while 之后，保持你原来的逻辑顺序
                while (window[ss] == mp[ss]) {
                    window[s.substr(left, len)]--;
                    left += len;
                    //window.clear(); // 你原来的代码注释掉了这行，保持不变
                }
                window[ss]++; // 放在这里匹配你原来的逻辑

                // 窗口大小判断和添加结果的逻辑，保持不变
                if (right - left + len == n_words * len) {
                    ans.emplace_back(left);
                    // 添加结果后，收缩窗口的逻辑，保持不变
                    window[s.substr(left, len)]--;
                    left += len;
                }
                // --- 原来的内部逻辑结束 ---
            }
        }

        return ans;
    }
};