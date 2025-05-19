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

using namespace std;

class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        unordered_map<string, int> mp;
        int ans = 0;

        for (int i = 0; i + minSize <= s.size(); ++i) {
            string subs = s.substr(i, minSize);
            unordered_set<char> unique_letters(subs.begin(), subs.end());

            if (unique_letters.size() <= maxLetters) {
                mp[subs]++;
                ans = max(ans, mp[subs]);
            }
        }

        return ans;
    }
};
