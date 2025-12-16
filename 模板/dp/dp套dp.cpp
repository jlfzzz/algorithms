#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

const int MOD = 998244353;

// https://atcoder.jp/contests/abc391/tasks/abc391_g

void solve() {
    int N, M;
    string S;
    if (!(cin >> N >> M >> S))
        return;

    int limit = 1 << N;

    // 1. 预处理 (Build Automaton)
    // trans[mask][c] 表示：当前差分状态为 mask，新加入字符 c ('a'+c) 后，新的差分状态是多少
    vector<vector<int>> trans(limit, vector<int>(26));

    for (int mask = 0; mask < limit; ++mask) {
        // --- 解码 (Decode) ---
        // 将二进制 mask 还原为 LCS 长度数组
        // lcs[i] 表示 S 的前 i 个字符与当前 T 的 LCS 长度
        vector<int> lcs(N + 1);
        lcs[0] = 0;
        for (int i = 0; i < N; ++i) {
            // mask 的第 i 位为 1 表示 lcs[i+1] - lcs[i] = 1
            // mask 的第 i 位为 0 表示 lcs[i+1] - lcs[i] = 0
            lcs[i + 1] = lcs[i] + ((mask >> i) & 1);
        }

        // --- 转移 (Transition) ---
        // 枚举下一个可能的字符 c (0~25)
        for (int c = 0; c < 26; ++c) {
            char char_to_add = 'a' + c;

            vector<int> next_lcs(N + 1);
            next_lcs[0] = 0;

            // 标准 LCS 动态规划转移方程
            // dp[i][j] 的一维滚动视角
            for (int i = 0; i < N; ++i) {
                if (S[i] == char_to_add) {
                    // 如果字符匹配：dp[i][j] = dp[i-1][j-1] + 1
                    // 对应这里就是 next_lcs[i+1] = lcs[i] + 1
                    next_lcs[i + 1] = lcs[i] + 1;
                } else {
                    // 如果字符不匹配：dp[i][j] = max(dp[i-1][j], dp[i][j-1])
                    // 对应这里就是 max(新算的上一位, 旧算的当前位)
                    next_lcs[i + 1] = max(next_lcs[i], lcs[i + 1]);
                }
            }

            // --- 编码 (Encode) ---
            // 将新的 LCS 数组重新压缩成 mask
            int next_mask = 0;
            for (int i = 0; i < N; ++i) {
                // 如果差值为 1，则将第 i 位置为 1
                if (next_lcs[i + 1] - next_lcs[i] == 1) {
                    next_mask |= (1 << i);
                }
            }

            // 记录转移结果
            trans[mask][c] = next_mask;
        }
    }

    // 2. 外层 DP (Path Counting)
    // dp[i][mask] 表示构造了长度为 i 的字符串 T，使得 LCS 状态为 mask 的方案数
    // N <= 10, M <= 100，可以直接开二维数组，无需滚动优化
    vector<vector<long long>> dp(M + 1, vector<long long>(limit, 0));

    // 初始状态：长度为 0，mask 为 0 (全0数组)，方案数为 1
    dp[0][0] = 1;

    for (int i = 0; i < M; ++i) {
        for (int mask = 0; mask < limit; ++mask) {
            // 如果当前状态不可达，直接跳过
            if (dp[i][mask] == 0)
                continue;

            // 尝试添加 26 个字母中的任意一个
            for (int c = 0; c < 26; ++c) {
                int next_mask = trans[mask][c];

                // 累加方案数并取模
                dp[i + 1][next_mask] = (dp[i + 1][next_mask] + dp[i][mask]) % MOD;
            }
        }
    }

    // 3. 统计答案 (Collect Answers)
    // ans[k] 表示 LCS 长度恰好为 k 的字符串 T 的数量
    vector<long long> ans(N + 1, 0);

    for (int mask = 0; mask < limit; ++mask) {
        if (dp[M][mask] == 0)
            continue;

        // mask 中 1 的个数就是最终的 LCS 长度
        // __builtin_popcount 是 GCC 内置函数，计算二进制中 1 的个数
        // 如果不是 GCC 编译器，可以用 bitset<10>(mask).count() 代替
        int lcs_len = __builtin_popcount(mask);

        ans[lcs_len] = (ans[lcs_len] + dp[M][mask]) % MOD;
    }

    // 输出结果
    for (int i = 0; i <= N; ++i) {
        cout << ans[i] << (i == N ? "" : " ");
    }
    cout << endl;
}

int main() {
    // 关闭同步流，加速 I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
