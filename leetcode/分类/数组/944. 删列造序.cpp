#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string> &strs) {
        int ans = 0;
        for (int i = 0; i < strs[0].size(); i++) {
            int mx = strs[0][i];
            for (int j = 1; j < strs.size(); j++) {
                if (strs[j][i] < mx) {
                    ans++;
                    break;
                }
                mx = max(mx, (int)strs[j][i]);
            }
        }
        return ans;
    }
};