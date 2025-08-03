#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Gosper's Hack 高级方法

class Solution {
public:
    int maximumRows(vector<vector<int>> &matrix, int numSelect) {
        int col = matrix[0].size();
        int row = matrix.size();
        int ans = 0;
        vector<int> selected;
        unordered_map<int, int> map;

        auto dfs = [&](this auto &&dfs, int index) -> void {
            if (index == col) {
                int count = 0;
                for (int i = 0;i < row;i++) {
                    bool flag = true;
                    for (int j = 0;j < col;j++) {
                        if (matrix[i][j] && map[j] != 1) {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) count++;
                }
                ans = max(ans, count);
                return;
            }

            dfs(index + 1);

            if (numSelect > 0) {
                map[index] = 1;
                numSelect--;
                dfs(index + 1);
                numSelect++;
                map[index] = 0;
            }
            };
        dfs(0);
        return ans;
    }
};  