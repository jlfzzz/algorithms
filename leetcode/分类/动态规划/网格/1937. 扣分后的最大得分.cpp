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
    long long maxPoints(vector<vector<int>> &points) {
        int m = points.size();
        int n = points[0].size();
        vector<long long> f(n);
        for (int i = 0; i < m; ++i) {
            vector<long long> g(n);
            long long best = LLONG_MIN;
            // 正序遍历
            for (int j = 0; j < n; ++j) {
                best = max(best, f[j] + j);
                g[j] = max(g[j], best + points[i][j] - j);
            }
            best = LLONG_MIN;
            // 倒序遍历
            for (int j = n - 1; j >= 0; --j) {
                best = max(best, f[j] - j);
                g[j] = max(g[j], best + points[i][j] + j);
            }
            f = move(g);
        }
        return *max_element(f.begin(), f.end());
    }
};