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
    long long mostPoints(vector<vector<int>> &questions) {
        int n = questions.size();
        vector<long long> f(n + 1);
        for (int i = n - 1; i >= 0; i--) {
            int j = min(i + questions[i][1] + 1, n);
            f[i] = max(f[i + 1], f[j] + questions[i][0]);
        }
        return f[0];
    }
};

class Solution {
public:
    long long mostPoints(vector<vector<int>> &questions) {
        int n = questions.size();
        vector<long long> f(n + 1);
        for (int i = 0; i < n; i++) {
            f[i + 1] = max(f[i + 1], f[i]);
            auto &q = questions[i];
            int j = min(i + q[1] + 1, n);
            f[j] = max(f[j], f[i] + q[0]);
        }
        return f[n];
    }
};
