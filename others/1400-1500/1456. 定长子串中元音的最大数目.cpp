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

using namespace std;

class Solution {
public:
    int maxVowels(string s, int k) {
        int n = s.size();
        int count = 0;
        int left = 0;
        int ans = 0;
        for (int right = 0; right < n; right++) {
            char c = s[right];
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                count++;
            }

            if (right - left + 1 == k) {
                ans = max(ans, count);
                if (s[left] == 'a' || s[left] == 'e' || s[left] == 'i' || s[left] == 'o' || s[left] == 'u') {
                    count--;
                }
                left++;
            }
            if (ans == k) break;
        }
        return ans;
    }
};