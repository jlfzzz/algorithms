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
    string minWindow(string s, string t) {
        int s_len = s.size();
        int t_len = t.size();

        unordered_map<char, int> t_map;
        unordered_map<char, int> window_map;

        for (int i = 0; i < t_len; i++) {
            t_map[t[i]]++;
        }

        int left = 0;
        int matches = 0;
        int target_matches = t_map.size();
        int ans_idx = 0;
        int ans_len = s_len + 1;

        for (int right = 0; right < s_len; right++) {
            char c = s[right];
            if (t_map[c]) {
                if (window_map[c] + 1 == t_map[c]) {
                    matches++;
                }
                window_map[c]++;
            }

            while (matches == target_matches) {
                if (right - left + 1 < ans_len) {
                    ans_idx = left;
                    ans_len = right - left + 1;
                }

                if (t_map[s[left]]) {
                    window_map[s[left]]--;
                    if (window_map[s[left]] < t_map[s[left]]) {
                        matches--;
                    }
                }

                left++;
            }
        }

        if (ans_len == s_len + 1) {
            return "";
        } else {
            return s.substr(ans_idx, ans_len);
        }
    }
};