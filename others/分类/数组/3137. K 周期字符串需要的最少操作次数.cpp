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
    int minimumOperationsToMakeKPeriodic(string word, int k) {
        int n = word.size();
        unordered_map<string, int> map;

        for (int i = 0; i < n; i++) {
            if (i % k == 0) {
                map[word.substr(i, k)]++;
                
            }
        }

        int ans = 0;
        for (auto &p : map) {
            if (p.second > ans) {
                ans = p.second;
            }
        }
        return (n - k * ans) / k;
    }
};