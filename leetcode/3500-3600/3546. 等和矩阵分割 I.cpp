#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

using namespace std;

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        ll total_sum = 0LL;
        for (auto& v : grid) {
            total_sum += accumulate(v.begin(), v.end(), 0LL);
        }

        if (total_sum & 1) return false;

        ll target_sum = total_sum >> 1;
        ll current_sum = 0LL;
        for (auto& v : grid) {
            current_sum += accumulate(v.begin(), v.end(), 0LL);
            if (current_sum == target_sum) return true;
            if (current_sum > target_sum) break;
        }

        current_sum = 0LL;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                current_sum += grid[j][i];
                if (current_sum == target_sum) return true;
                if (current_sum > target_sum) break;
            }
        }
        return false;
    }
};

class Solution {
    public:
        bool canPartitionGrid(vector<vector<int>> &grid) {
            int n = grid.size();
            int m = grid[0].size();
    
            // 计算总和
            long long total_sum = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    total_sum += grid[i][j];
                }
            }
    
            // 如果总和为奇数，无法分割成两个相等的部分
            if (total_sum % 2 == 1) {
                return false;
            }
            
            long long target = total_sum / 2;
            
            // 检查水平分割
            vector<long long> prefix_row_sum(n + 1, 0);
            for (int i = 0; i < n; i++) {
                long long row_sum = 0;
                for (int j = 0; j < m; j++) {
                    row_sum += grid[i][j];
                }
                prefix_row_sum[i + 1] = prefix_row_sum[i] + row_sum;
            }
            
            // 检查每一个可能的水平分割位置
            for (int i = 1; i < n; i++) {
                if (prefix_row_sum[i] == target) {
                    return true;
                }
            }
            
            // 检查垂直分割
            vector<long long> prefix_col_sum(m + 1, 0);
            for (int j = 0; j < m; j++) {
                long long col_sum = 0;
                for (int i = 0; i < n; i++) {
                    col_sum += grid[i][j];
                }
                prefix_col_sum[j + 1] = prefix_col_sum[j] + col_sum;
            }
            
            // 检查每一个可能的垂直分割位置
            for (int j = 1; j < m; j++) {
                if (prefix_col_sum[j] == target) {
                    return true;
                }
            }
            
            return false;
        }
    }; 