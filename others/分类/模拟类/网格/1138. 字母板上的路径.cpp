#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;
// 这种处理乱序，用map， solution2优化

class Solution {
public:
    string alphabetBoardPath(string target) {
        unordered_map<char, pair<int, int>> board;

        // 填充5x5网格的映射
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                char ch = 'a' + 5 * i + j;
                board[ch] = make_pair(i, j);
            }
        }
        board['z'] = { 5, 0 };
        pair<int, int> pos = { 0, 0 };
        string ans = "";
        for (auto &c : target) {
            auto targetChar = board[c];
            int rowOffset = targetChar.first - pos.first;
            int colOffset = targetChar.second - pos.second;

            pos = board[c];
            string v = "";
            string h = "";
            if (rowOffset < 0) {
                v += string(abs(rowOffset), 'U');
            } else if (rowOffset > 0) {
                v += string(rowOffset, 'D');
            }

            if (colOffset < 0) {
                h += string(abs(colOffset), 'L');
            } else if (colOffset > 0) {
                h += string(colOffset, 'R');
            }
            ans += (c == 'z' ? h + v : v + h) + '!';
        }
        return ans;

    }
};

class Solution2 {
public:
    string alphabetBoardPath(string target) {
        string ans;
        int x = 0, y = 0;
        for (char c : target) {
            int nx = (c - 'a') / 5, ny = (c - 'a') % 5; // 目标位置
            string v(abs(nx - x), "UD"[nx > x]); // 竖直
            string h(abs(ny - y), "LR"[ny > y]); // 水平
            ans += (c != 'z' ? v + h : h + v) + "!";
            x = nx, y = ny;
        }
        return ans;
    }
};
