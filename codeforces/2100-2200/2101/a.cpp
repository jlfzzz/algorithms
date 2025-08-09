#include <iostream>
#include <vector>
using namespace std;

void magical_spiral(int n) {
    // 初始化 n×n 网格，用 -1 表示未填充
    vector<vector<int>> arr(n, vector<int>(n, -1));

    // 确定起始中心位置
    int x, y;
    if (n % 2 == 0) {
        x = n / 2 - 1;
        y = n / 2 - 1;
    } else {
        x = n / 2;
        y = n / 2;
    }

    // 从中心开始，放置数字 0
    arr[x][y] = 0;
    int value = 1;
    int step = 1;

    // 四个方向：右、下、左、上
    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (value < n * n) {
        for (int d = 0; d < 4; d++) {
            int steps = step;

            // 每两个方向（右左、下上）后步数增加
            if (d % 2 == 1)
                step++;

            int dx = dir[d][0];
            int dy = dir[d][1];

            for (int i = 0; i < steps; i++) {
                x += dx;
                y += dy;

                // 检查边界并填充
                if (x >= 0 && x < n && y >= 0 && y < n && arr[x][y] == -1) {
                    arr[x][y] = value;
                    value++;
                }

                if (value >= n * n)
                    break;
            }

            if (value >= n * n)
                break;
        }
    }

    // 输出结果
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j];
            if (j < n - 1)
                cout << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        magical_spiral(n);
    }

    return 0;
}
