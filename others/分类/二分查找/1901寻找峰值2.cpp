#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

//解析
/*
不能从每行找峰值然后去检查是否是二维峰值，会漏
要从中间行开始二分，直接找每行的最大值，再上下比较，
进化逐行的二分
而不是每行的单独二分
class Solution {
public:
    bool check(int row, int col, vector<vector<int>> &mat) {
        int upper = row - 1;
        int lower = row + 1;
        int left = col - 1;
        int right = col + 1;
        int rowLimit = mat.size();
        int colLimit = mat[0].size();
        int current = mat[row][col];

        if (upper != -1 && mat[upper][col] >= current) {
            return false;
        }

        if (lower != rowLimit && mat[lower][col] >= current) {
            return false;
        }

        if (left != -1 && mat[row][left] >= current) {
            return false;
        }

        if (right != colLimit && mat[row][right] >= current) {
            return false;
        }

        return true;
    }

    vector<int> findPeakGrid(vector<vector<int>> &mat) {
        // 想法：行遍历，每行用二分，上坡下坡
        int row = mat.size();
        for (int i = 0; i < row; i++) {
            int left = -1;
            int right = mat[0].size();
            int ans = 0;
            int n = mat[0].size();

            while (left + 1 < right) {
                int mid = left + (right - left) / 2;
                if (mid == n - 1) {
                    right = mid;
                    continue;
                }

                if (mat[i][mid] > mat[i][mid + 1]) {
                    right = mid;
                } else {
                    left = mid;
                }
            }
            if (check(i, right, mat)) {
                return vector<int>{i, right};
            }
        }
        return vector<int>{-1, -1};
    }
};
*/

class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>> &mat) {
        int upperRow = -1;
        int lowerRow = mat.size();

        while (upperRow + 1 < lowerRow) {
            int midRow = upperRow + (lowerRow - upperRow) / 2;
            int maxRowValIndex = ranges::max_element(mat[midRow]) - mat[midRow].begin();

            if ((midRow == mat.size() - 1) ||
                (mat[midRow][maxRowValIndex] > mat[midRow + 1][maxRowValIndex])) {
                lowerRow = midRow;
            } else {
                upperRow = midRow;
            }
        }
        return { lowerRow, (int)(ranges::max_element(mat[lowerRow]) - mat[lowerRow].begin()) };
    }
};
