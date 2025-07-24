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
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size(), m = s2.size();
        if (n + m != s3.size()) {
            return false;
        }

        vector f(n + 1, vector<int>(m + 1));
        f[0][0] = true;
        for (int j = 0; j < m; j++) {
            f[0][j + 1] = s2[j] == s3[j] && f[0][j];
        }
        for (int i = 0; i < n; i++) {
            f[i + 1][0] = s1[i] == s3[i] && f[i][0];
            for (int j = 0; j < m; j++) {
                f[i + 1][j + 1] = s1[i] == s3[i + j + 1] && f[i][j + 1] ||
                    s2[j] == s3[i + j + 1] && f[i + 1][j];
            }
        }
        return f[n][m];
    }
};