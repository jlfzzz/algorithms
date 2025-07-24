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
    int minDistance(string word1, string word2) {
        int n = word1.length(), m = word2.length();
        vector f(n + 1, vector<int>(m + 1));
        f[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            f[i][0] = i;
        }

        for (int i = 1; i <= m; i++) {
            f[0][i] = i;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                f[i + 1][j + 1] = word1[i] == word2[j] ? f[i][j] :
                    min(min(f[i][j + 1], f[i + 1][j]), f[i][j]) + 1;
            }
        }
        return f[n][m];
    }
};