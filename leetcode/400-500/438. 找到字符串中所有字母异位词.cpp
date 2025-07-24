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
    vector<int> findAnagrams(string s, string p) {
        vector<int> ans;
        int s_len = s.size();
        int p_len = p.size();
        unordered_map<char, int> window;
        unordered_map<char, int> p_map;

        for (char c : p) {
            p_map[c]++;
        }
        int matches = 0;
        int matches_needed = p_map.size();

        int left = 0;
        for (int right = 0; right < s_len; right++) {
            char c = s[right];
            if (p_map[c]) {
                if (window[c] + 1 == p_map[c]) {
                    matches++;
                } else if (window[c] == p_map[c]) {
                    matches--;
                }
                window[c]++;
            }

            if (right - left + 1 == p_len) {
                if (matches == matches_needed) {
                    ans.emplace_back(left);
                }

                if (p_map[s[left]]) {
                    if (window[s[left]] - 1 == p_map[s[left]]) {
                        matches++;
                    } else if (window[s[left]] == p_map[s[left]]) {
                        matches--;
                    }
                }
                window[s[left]]--;
                left++;
            }
        }

        return ans;
    }
};