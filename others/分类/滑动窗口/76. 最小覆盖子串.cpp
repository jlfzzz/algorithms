#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <ranges>
#include <numeric>

using namespace std;

class Solution {
public:
    bool check(unordered_map<char, int> &target, unordered_map<char, int> &source) {
        for (const auto &pair : target) {
            if (source[pair.first] < pair.second) {
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        if (s.empty() || t.empty()) return "";

        unordered_map<char, int> target;
        for (char c : t) {
            target[c]++;
        }

        unordered_map<char, int> source;
        int left = 0;
        int ansLength = INT_MAX;
        int ansStart = 0;

        for (int right = 0; right < s.length(); right++) {
            source[s[right]]++;

            while (check(target, source)) {
                if (right - left + 1 < ansLength) {
                    ansLength = right - left + 1;
                    ansStart = left;
                }
                source[s[left]]--;
                left++;
            }
        }

        return ansLength == INT_MAX ? "" : s.substr(ansStart, ansLength);
    }



















    // string minWindow(string s, string t) {
                                                                    //     unordered_map<char, int> map;
    //     unordered_map<char, int> targetMap;
    //     for (const char &c : t) {
    //         map[c]++;
    //         targetMap[c]++;
    //     }

    //     string ans("");
    //     string str{ "" };
    //     int left = 0;
    //     for (int right = 0; right < s.length(); right++) {
    //         ans = ans.length() > (right - left + 1) ? str.substr(left) : ans;

    //         str += s[right];

    //         if (map.count(s[right])) {
    //             map[s[right]]--;
    //             if (map[s[right]] == 0) {
    //                 map.erase(s[right]);
    //             }
    //         }

    //         while (map.empty()) {
    //             if (ans.empty() || (right - left + 1) < ans.size()) {
    //                 ans = s.substr(left, right - left + 1);
    //             }

    //             if (targetMap.count(s[left])) {
    //                 // 如果左侧字符属于目标，则加回该字符
    //                 map[s[left]]++;
    //                 left++;
    //                 // 一旦将目标字符数恢复到所需值以上，窗口就不再有效，跳出内层循环
    //                 break;
    //             } else {
    //                 // 非目标字符直接缩小窗口
    //                 left++;
    //             }
    //         }


    //     }

    //     return ans;
    //}
};