#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>> &matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        int ans = 0;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (matrix[i - 1][j - 1] == '0') {
                    continue;
                } else {
                    dp[i][j] = 1;
                    if (dp[i - 1][j] > 0 &&
                        dp[i][j - 1] > 0 &&
                        dp[i - 1][j - 1] > 0) {
                        dp[i][j] += min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
                    }
                }
                ans = max(ans, dp[i][j]);
            }
        }

        return ans * ans;
    }
};



class Solution {
public:
    int maximalSquare(vector<vector<char>> &matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return 0;
        }
        int maxSide = 0;
        int rows = matrix.size(), columns = matrix[0].size();
        vector<vector<int>> dp(rows, vector<int>(columns));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (matrix[i][j] == '1') {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                    }
                    maxSide = max(maxSide, dp[i][j]);
                }
            }
        }
        int maxSquare = maxSide * maxSide;
        return maxSquare;
    }
};
