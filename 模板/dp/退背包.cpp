#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 998244353;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) { return power(n, MOD - 2); }


// https://codeforces.com/gym/105948/problem/H
// 退背包，先一遍01背包求总方案数，然后减掉x的贡献，求除了它的所有方案数
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> a(n);
    int max_sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        max_sum += a[i];
    }


    vector<vector<long long>> C(n + 1, vector<long long>(n + 1));
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(max_sum + 1, 0));

    dp[0][0] = 1;


    // 标准01背包求方案数。
    for (int x: a) {
        for (int i = n; i >= 1; i--) {
            for (int s = max_sum; s >= x; s--) {
                dp[i][s] = (dp[i][s] + dp[i - 1][s - x]) % MOD;
            }
        }
    }

    vector<long long> ans_numerator(n + 1, 0);

    // 遍历每个元素，进行“退背包”操作
    for (int x: a) {
        // 复制一份 dp 表作为当前不包含 x 的状态表 g
        vector<vector<long long>> g = dp;

        // 撤销操作 (Revocation)
        // 必须正序遍历
        for (int i = 1; i <= n; i++) {
            for (int s = x; s <= max_sum; s++) {
                // g[i][s] = dp[i][s] - g[i-1][s-x]
                g[i][s] = (g[i][s] - g[i - 1][s - x] + MOD) % MOD;
            }
        }

        // 统计贡献
        for (int k = 2; k <= n; k++) {
            // 我们需要选 k-1 个其他人，使得 sum < (k-1) * x
            long long limit = (long long) (k - 1) * x;

            // 累加满足条件的方案数
            // 如果 limit > max_sum，只需累加到 max_sum 即可
            for (int s = 0; s < limit && s <= max_sum; s++) {
                ans_numerator[k] = (ans_numerator[k] + g[k - 1][s]) % MOD;
            }
        }
    }

    // 4. 计算最终期望并输出
    for (int k = 2; k <= n; k++) {
        // 分子：ans_numerator[k]
        // 分母：C(n, k) * k
        // 期望 = (Sum of Valid Counts) / (Total Combinations * Length)

        long long denominator = (C[n][k] * k) % MOD;
        long long result = (ans_numerator[k] * modInverse(denominator)) % MOD;

        cout << result << (k == n ? "" : " ");
    }
    cout << endl;

    return 0;
}
