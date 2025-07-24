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
#include <random>

using namespace std;

class Solution {
public:
    vector<string> getLongestSubsequence(vector<string> &words,
        vector<int> &groups) {
        vector<string> ans;
        int n = groups.size();

        for (int i = 0; i < n; i++) {
            if (i == n - 1 || groups[i] != groups[i + 1]) {
                ans.push_back(words[i]);
            }
        }
        return ans;
    }
};