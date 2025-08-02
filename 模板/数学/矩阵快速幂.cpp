#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> DIRS = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
using ll = long long;
constexpr int MOD = int(1e9 + 7);

using Matrix = vector<vector<ll>>;

// 矩阵乘法，缓存友好版本。先算一整行的
Matrix mat_mul(const Matrix &m1, const Matrix &m2) {
    int n = m1.size();
    int p = m1[0].size();
    int m = m2[0].size();

    Matrix ret(n, vector<ll>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < p; ++k) {
            if (m1[i][k] == 0) {
                continue;
            }
            for (int j = 0; j < m; ++j) {
                ret[i][j] = (ret[i][j] + m1[i][k] * m2[k][j]) % MOD;
            }
        }
    }
    return ret;
}

// 矩阵快速幂
Matrix quick_mul(Matrix mat, int n) {
    int m = mat.size();
    Matrix unit(m, vector<ll>(m, 0));
    for (int i = 0; i < m; ++i) {
        unit[i][i] = 1;
    }

    while (n) {
        if (n & 1) {
            unit = mat_mul(mat, unit);
        }
        mat = mat_mul(mat, mat);
        n >>= 1;
    }
    return unit;
}



// lc3337 调用示例
class Solution {
public:
    int lengthAfterTransformations(string s, int t, vector<int> &nums) {
        int SIZE = 26;
        Matrix mat(SIZE, vector<ll>(SIZE, 0));
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int m = nums[i];
            for (int j = 0; j < m; ++j) {
                mat[(i + j + 1) % SIZE][i] += 1;
            }
        }

        mat = quick_mul(mat, t);

        Matrix mat2(SIZE, vector<ll>(1, 0));
        for (char c: s) {
            mat2[c - 'a'][0] += 1;
        }

        mat = mat_mul(mat, mat2);

        ll total = 0;
        for (int i = 0; i < SIZE; ++i) {
            total += mat[i][0];
        }
        return total % MOD;
    }
};
