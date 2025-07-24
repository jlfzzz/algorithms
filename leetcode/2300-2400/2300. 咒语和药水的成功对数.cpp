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
    vector<int> successfulPairs(vector<int> &spells, vector<int> &potions, long long success) {
        vector<int> ans;
        //int n = potions.size();
        for (int spell : spells) {
            int target = (success + spell - 1) / spell;
            auto it = ranges::lower_bound(potions, target);
            ans.emplace_back(potions.end() - it);
        }
        return ans;
    }
};