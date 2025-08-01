#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> DIRS = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
using ll = long long;
constexpr int MOD = int(1e9 + 7);

using matrix = vector<vector<long long>>;

// 返回矩阵 a 和矩阵 b 相乘的结果
matrix mul(matrix &a, matrix &b) {
    int n = a.size(), m = b[0].size();
    matrix c = matrix(n, vector<long long>(m));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < a[i].size(); k++) {
            if (a[i][k] == 0) {
                continue;
            }
            for (int j = 0; j < m; j++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}

// a^n * f0
matrix pow_mul(matrix a, int n, matrix &f0) {
    matrix res = f0;
    while (n) {
        if (n & 1) {
            res = mul(a, res);
        }
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}


// 下面是调用，lc935
class Solution {
public:
    int knightDialer(int n) {
        if (n == 1) {
            return 10;
        }
        matrix f0 = {{1}, {1}, {1}, {1}};
        matrix m = {
            {0, 1, 1, 0},
            {2, 0, 0, 0},
            {2, 0, 0, 1},
            {0, 0, 2, 0},
        };
        m = pow_mul(m, n - 1, f0);
        return (m[0][0] * 4 + m[1][0] * 2 + m[2][0] * 2 + m[3][0]) % MOD;
    }
};
