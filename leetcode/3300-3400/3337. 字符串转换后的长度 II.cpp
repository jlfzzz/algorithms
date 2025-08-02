#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);


class Solution {
public:
    static constexpr int MOD = 1'000'000'007;
    using Matrix = vector<vector<ll>>;

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
};




class Solution {
public:
    static constexpr int MOD = 1'000'000'007;
    static constexpr int SIZE = 26;

    using Matrix = array<array<int, SIZE>, SIZE>;

    // 固定 26x26两个矩阵相乘
    Matrix mat_mul(Matrix &m1, Matrix &m2) {
        Matrix ret{};
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                for (int k = 0; k < 26; k++) {
                    ret[i][j] = (ret[i][j] + 1LL * m1[i][k] * m2[k][j] % MOD) % MOD;
                }
            }
        }
        return ret;
    }

    Matrix mat_quick_pow(Matrix &origin, int power) {
        Matrix ret{};
        for (int i = 0; i < 26; i++) {
            ret[i][i] = 1;
        }

        Matrix base = origin;
        while (power > 0) {
            if (power % 2 == 1) {
                ret = mat_mul(ret, base);
            }

            base = mat_mul(base, base);
            power = power / 2;
        }
        return ret;
    }

    int lengthAfterTransformations(string s, int t, vector<int> &nums) {
        Matrix m{}; // 初始化所有元素为0
        vector<int> record(26, 0);

        for (char c: s) {
            record[c - 'a']++;
        }

        for (int i = 0; i < 26; i++) {
            for (int j = 1; j <= nums[i]; j++) {
                m[(i + j) % 26][i] = 1;
            }
        }

        m = mat_quick_pow(m, t);
        long long ans = 0;
        for (int i = 0; i < 26; i++) {
            long long sum = 0;
            for (int j = 0; j < 26; j++) {
                sum = (sum + 1LL * m[i][j] * record[j] % MOD) % MOD;
            }
            ans = (ans + sum) % MOD;
        }
        return ans;
    }
};


class Solution {
    static constexpr int MOD = 1'000'000'007;
    static constexpr int SIZE = 26;

    using Matrix = array<array<int, SIZE>, SIZE>;

    // 返回矩阵 a 和矩阵 b 相乘的结果
    Matrix mul(Matrix &a, Matrix &b) {
        Matrix c{};
        for (int i = 0; i < SIZE; i++) {
            for (int k = 0; k < SIZE; k++) {
                if (a[i][k] == 0) {
                    continue;
                }
                for (int j = 0; j < SIZE; j++) {
                    c[i][j] = (c[i][j] + (long long) a[i][k] * b[k][j]) % MOD;
                }
            }
        }
        return c;
    }

    // 返回 n 个矩阵 a 相乘的结果
    Matrix pow(Matrix a, int n) {
        Matrix res = {};
        for (int i = 0; i < SIZE; i++) {
            res[i][i] = 1; // 单位矩阵
        }
        while (n) {
            if (n & 1) {
                res = mul(res, a);
            }
            a = mul(a, a);
            n >>= 1;
        }
        return res;
    }

public:
    int lengthAfterTransformations(string s, int t, vector<int> &nums) {
        Matrix m{};
        for (int i = 0; i < SIZE; i++) {
            for (int j = i + 1; j <= i + nums[i]; j++) {
                m[i][j % SIZE] = 1;
            }
        }
        Matrix mt = pow(m, t);

        int cnt[SIZE]{};
        for (char c: s) {
            cnt[c - 'a']++;
        }

        long long ans = 0;
        for (int i = 0; i < SIZE; i++) {
            // m 第 i 行的和就是 f[t][i]
            ans += reduce(mt[i].begin(), mt[i].end(), 0LL) * cnt[i];
        }
        return ans % MOD;
    }
};
