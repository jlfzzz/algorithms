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
#include <stack>
#include <set>

using namespace std;

class Solution {
public:
    int maximumLengthSubstring(string s) {
        int n = s.size();
        int ans = 0;
        int left = 0;
        unordered_map<char, int> mp;
        for (int right = 0; right < n; right++) {
            char c = s[right];
            mp[c]++;
            while (mp[c] > 2) {
                mp[s[left]]--;
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};