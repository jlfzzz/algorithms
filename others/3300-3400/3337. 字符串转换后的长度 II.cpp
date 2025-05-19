#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>
#include <queue>
#include <cstring>
#include <array> 
#include <bitset>
#include <stack>
#include <set>
#include <random>

using namespace std;

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
        Matrix m{};  // 初始化所有元素为0
        vector<int> record(26, 0);

        for (char c : s) {
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
    Matrix mul(Matrix& a, Matrix& b) {
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
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        Matrix m{};
        for (int i = 0; i < SIZE; i++) {
            for (int j = i + 1; j <= i + nums[i]; j++) {
                m[i][j % SIZE] = 1;
            }
        }
        Matrix mt = pow(m, t);

        int cnt[SIZE]{};
        for (char c : s) {
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