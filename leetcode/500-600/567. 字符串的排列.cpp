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

using namespace std;

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.length();
        int n2 = s2.length();

        // 如果 s1 比 s2 长，s2 不可能包含 s1 的排列
        if (n1 > n2) {
            return false;
        }

        // 使用数组记录 s1 和当前窗口的字符频率
        vector<int> s1_counts(26, 0);
        vector<int> window_counts(26, 0);

        // 计算 s1 的字符频率，并初始化第一个窗口的频率
        for (int i = 0; i < n1; ++i) {
            s1_counts[s1[i] - 'a']++;
            window_counts[s2[i] - 'a']++;
        }

        int matches = 0;
        for (int i = 0; i < 26; i++) {
            if (s1_counts[i] == window_counts[i]) {
                matches++;
            }
        }

        if (matches == 26) return true;

        for (int i = n1; i < n2; i++) {
            char curr_c = s2[i];
            int curr_c_idx = curr_c - 'a';

            if (s1_counts[curr_c_idx] == window_counts[curr_c_idx]) {
                window_counts[curr_c_idx]++;
                matches--;
            } else {
                window_counts[curr_c_idx]++;
                if (window_counts[curr_c_idx] == s1_counts[curr_c_idx]) {
                    matches++;
                }
            }

            int left_c_idx = s2[i - n1] - 'a';
            if (s1_counts[left_c_idx] == window_counts[left_c_idx]) {
                window_counts[left_c_idx]--;
                matches--;
            } else {
                window_counts[left_c_idx]--;
                if (window_counts[left_c_idx] == s1_counts[left_c_idx]) {
                    matches++;
                }
            }

            if (matches == 26) return true;
        }

        return  false;
    }
};