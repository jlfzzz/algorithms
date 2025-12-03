#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int (i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
const ll MOD2 = 4611686018427387847;
constexpr int inf = 100'000'005;


// a + b = (a ^ b) + 2 * (a & b)

int main() {
    // 定义一个 lambda 函数 f1，用于验证恒等式
    // 使用 auto 关键字自动推断类型
    // [&] 表示以引用的方式捕获所有外部变量（在此例中未使用，但遵从您的模板）
    auto f1 = [&](int a, int b) {
        // 为了防止整数溢出（例如 a 和 b 都很大时），我们使用 long long 来存储计算结果
        long long sum_val = (long long) a + b;
        long long xor_and_val = (long long) (a ^ b) + 2LL * (a & b);

        // 打印输入值和计算过程
        std::cout << "--- 验证 a = " << a << ", b = " << b << " ---" << std::endl;
        std::cout << "左边 (a + b): " << sum_val << std::endl;
        std::cout << "右边 (a^b + 2*(a&b)): " << xor_and_val << std::endl;

        // 比较两边的结果并打印验证结论
        if (sum_val == xor_and_val) {
            std::cout << "结论: 恒等式成立。" << std::endl;
        } else {
            // 理论上对于非负整数，这个分支不会被执行
            std::cout << "结论: 恒等式不成立！" << std::endl;
        }
        std::cout << std::endl; // 增加一个空行，方便阅读
    };

    // --- 使用 f1 函数进行测试 ---
    f1(10, 5);
    f1(13, 7);
    f1(12345, 67890);
    f1(0, 99);

    return 0;
}
