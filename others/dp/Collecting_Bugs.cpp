#include <iomanip>
#include <iostream>

using namespace std;

int n, s;
double dp[1010][1010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> s;

    dp[n][s] = 0.0; // 全部收集完，期望天数为 0

    // 从已收集数量 i, j = n,s 往 0 推
    for (int i = n; i >= 0; i--) {
        for (int j = s; j >= 0; j--) {
            if (i == n && j == s)
                continue; // 完成状态

            // 计算今天四种情况的概率
            double pi_new = (double) (n - i) / n; // 剩余类型比例
            double pi_old = (double) i / n; // 已收集类型比例
            double pj_new = (double) (s - j) / s; // 剩余子系统比例
            double pj_old = (double) j / s; // 已收集子系统比例

            // 四种事件对应的期望值
            double p1 = 0.0, p2 = 0.0, p3 = 0.0;
            // 新 type + 新 subsystem
            if (i < n && j < s)
                p1 = dp[i + 1][j + 1] * pi_new * pj_new;
            // 新 type + 旧 subsystem
            if (i < n)
                p2 = dp[i + 1][j] * pi_new * pj_old;
            // 旧 type + 新 subsystem
            if (j < s)
                p3 = dp[i][j + 1] * pi_old * pj_new;

            // 今天没进展的概率
            double p_no = pi_old * pj_old;

            // 今天消耗 1 天 + 三种有进展情况
            double total = 1.0 + p1 + p2 + p3;

            // 除以 1 - 概率没进展
            dp[i][j] = total / (1.0 - p_no);
        }
    }

    cout << fixed << setprecision(4) << dp[0][0] << "\n";
    return 0;
}
