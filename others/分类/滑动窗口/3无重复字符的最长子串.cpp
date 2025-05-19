/*
给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。



示例 1:

输入: s = "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:

输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:

输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
*/
#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include <set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int ans = 0;
        int left = 0;
        map<char, int> table;

        for (int i = 0; i < s.length(); ++i) {
            if (table.count(s.at(i))) {
                left = max(left, table[s[i]] + 1);
            }

            table[s[i]] = i;
            ans = max(ans, i - left + 1);
            //
        }

        return ans;
    }
};

class Solution2 {
public:
    int lengthOfLongestSubstring(string s) {
        int ans = 0;
        int left = 0;
        set<char> set;

        for (int i = 0; i < s.length(); ++i) {
            while (set.count(s[i])) {
                set.erase(s[left]);
                left++;
            }

            set.insert(s[i]);
            ans = max(ans, i - left + 1);
        }
    }
};




/*
int ans = 0;
        int left = 0;
        map<char, int> table;

        for (int right = 0; right < s.length(); ++right) {
            if (table.count(s.at(right))) {
                left = max(left, table[s.at(right)] + 1);
                //table[s.at(right)] = right;
                // for (int j = left; j < right; ++j) {
                //     table[s.at(j)] = 0;
                // }
            }
            table[s.at(right)] = right;
            ans = max(ans, right - left + 1);

        }
        return ans;
*/