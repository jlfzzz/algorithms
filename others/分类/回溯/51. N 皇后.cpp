#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<vector<int>> board(n, vector<int>(n, 0));  // 用来记录攻击次数
        vector<pair<int, int>> queenPos;                  // 存储皇后位置

        auto validPos = [&](int row, int col) -> bool {
            return row >= 0 && row < n && col >= 0 && col < n;
        };

        auto putQueen = [&](int row, int col, bool remove) -> void {
            int delta = remove ? 1 : -1;  // 放置时 delta = -1，撤销时 delta = +1
            for (int i = 0; i < n; i++) {
                board[row][i] += delta;  // 行
                board[i][col] += delta;  // 列
            }
            // 主对角线
            for (int i = 1; i < n; i++) {
                if (validPos(row + i, col + i)) board[row + i][col + i] += delta;
                if (validPos(row - i, col - i)) board[row - i][col - i] += delta;
            }
            // 副对角线
            for (int i = 1; i < n; i++) {
                if (validPos(row - i, col + i)) board[row - i][col + i] += delta;
                if (validPos(row + i, col - i)) board[row + i][col - i] += delta;
            }
        };

        auto dfs = [&](auto &&dfs, int put) -> void {
            if (put == n) {
                vector<string> s(n, string(n, '.'));
                for (auto &[i, j] : queenPos) {
                    s[i][j] = 'Q';
                }
                ans.emplace_back(s);
                return;
            }

            for (int j = 0; j < n; j++) { // ✅ 只尝试当前行 put 的每一列
                if (board[put][j] != 0) continue;
                putQueen(put, j, false);
                queenPos.emplace_back(put, j);
                dfs(dfs, put + 1);
                queenPos.pop_back();
                putQueen(put, j, true);
            }
        };

        dfs(dfs, 0);
        return ans;
    }
};

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        auto solutions = vector<vector<string>>();
        auto queens = vector<int>(n, -1);
        auto columns = unordered_set<int>();
        auto diagonals1 = unordered_set<int>();
        auto diagonals2 = unordered_set<int>();
        backtrack(solutions, queens, n, 0, columns, diagonals1, diagonals2);
        return solutions;
    }

    void backtrack(vector<vector<string>> &solutions, vector<int> &queens, int n, int row, unordered_set<int> &columns, unordered_set<int> &diagonals1, unordered_set<int> &diagonals2) {
        if (row == n) {
            vector<string> board = generateBoard(queens, n);
            solutions.push_back(board);
        } else {
            for (int i = 0; i < n; i++) {
                if (columns.find(i) != columns.end()) {
                    continue;
                }
                int diagonal1 = row - i;
                if (diagonals1.find(diagonal1) != diagonals1.end()) {
                    continue;
                }
                int diagonal2 = row + i;
                if (diagonals2.find(diagonal2) != diagonals2.end()) {
                    continue;
                }
                queens[row] = i;
                columns.insert(i);
                diagonals1.insert(diagonal1);
                diagonals2.insert(diagonal2);
                backtrack(solutions, queens, n, row + 1, columns, diagonals1, diagonals2);
                queens[row] = -1;
                columns.erase(i);
                diagonals1.erase(diagonal1);
                diagonals2.erase(diagonal2);
            }
        }
    }

    vector<string> generateBoard(vector<int> &queens, int n) {
        auto board = vector<string>();
        for (int i = 0; i < n; i++) {
            string row = string(n, '.');
            row[queens[i]] = 'Q';
            board.push_back(row);
        }
        return board;
    }
};



/*
这是错的*/
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<vector<int>> board(n, vector<int>(n, 0));  // 改用 int 记录攻击次数
        vector<pair<int, int>> queenPos;                  // 动态存储皇后位置

        auto validPos = [&](int row, int col) -> bool {
            return row >= 0 && row < n && col >= 0 && col < n;
            };

        auto putQueen = [&](int row, int col, bool put) -> void {
            int delta = put ? 1 : -1;
            // put=false 时增加攻击，put=true 时减少攻击
            for (int i = 0; i < n; i++) {
                board[row][i] += delta;  // 行
                board[i][col] += delta;  // 列
            }
            // 主对角线（左上到右下）
            for (int i = 1; i < n; i++) {
                if (validPos(row + i, col + i)) board[row + i][col + i] += delta;
                if (validPos(row - i, col - i)) board[row - i][col - i] += delta;
            }
            // 副对角线（右上到左下）
            for (int i = 1; i < n; i++) {
                if (validPos(row - i, col + i)) board[row - i][col + i] += delta;
                if (validPos(row + i, col - i)) board[row + i][col - i] += delta;
            }
            };

        auto dfs = [&](this auto &&dfs, int put) -> void {
            if (put == n) {
                vector<string> s(n, string(n, '.'));
                for (auto &[i, j] : queenPos) {
                    s[i][j] = 'Q';
                }
                ans.emplace_back(s);
                return;
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (board[i][j] != 0) continue;  // 只能放在未被攻击的位置
                    putQueen(i, j, false);            // 放置皇后并更新攻击范围
                    queenPos.emplace_back(i, j);     // 记录位置
                    dfs(put + 1);                    // 递归
                    queenPos.pop_back();              // 回溯
                    putQueen(i, j, true);             // 撤销皇后并恢复攻击范围
                }
            }
            };

        dfs(0);
        return ans;
    }
};

