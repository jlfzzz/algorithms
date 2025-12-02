// combinatorics_identities.cpp
//
// 内容：
//   1. 组合数 C(n, k) 的含义与预处理
//   2. 帕斯卡公式（Pascal identity）
//   3. 范德蒙德公式（Vandermonde's identity）
//   4. Hockey-stick 恒等式（∑C(m, t) = C(n+1, t+1)）

#include <bits/stdc++.h>
using namespace std;

constexpr int NMAX = 30;

long long C_table[NMAX + 1][NMAX + 1];

void build_combinations() {
    for (int n = 0; n <= NMAX; ++n) {
        C_table[n][0] = C_table[n][n] = 1;
        for (int k = 1; k < n; ++k) {
            // 这里用的正是“帕斯卡公式”：
            // C(n, k) = C(n-1, k-1) + C(n-1, k)
            C_table[n][k] = C_table[n - 1][k - 1] + C_table[n - 1][k];
        }
    }
}

// 安全封装一下，附带边界处理
long long C(int n, int k) {
    if (n < 0 || k < 0 || k > n || n > NMAX)
        return 0;
    return C_table[n][k];
}

// 打印一个小表，方便你肉眼看 C(n, k)
void demo_print_combinations(int n) {
    cout << "=== C(n, k) for n <= " << n << " ===\n";
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            cout << "C(" << i << "," << j << ")=" << C(i, j) << "  ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// 1. 帕斯卡公式：C(n, k) = C(n-1, k-1) + C(n-1, k)
void demo_pascal_identity(int upto_n) {
    cout << "=== Pascal identity: C(n, k) = C(n-1, k-1) + C(n-1, k) ===\n";
    for (int n = 1; n <= upto_n; ++n) {
        for (int k = 1; k < n; ++k) {
            long long left = C(n, k);
            long long right = C(n - 1, k - 1) + C(n - 1, k);
            cout << "n=" << n << ", k=" << k << " : "
                 << "C(" << n << "," << k << ") = " << left << " , C(" << n - 1 << "," << k - 1 << ") + C(" << n - 1
                 << "," << k << ") = " << right << (left == right ? "  [OK]\n" : "  [MISMATCH]\n");
        }
    }
    cout << "\n";

    /*
     * 组合解释（中文）：
     *   从 n 个人中选 k 个，记其中一个特殊的人为“X”。
     *   所有选法分两类：
     *     1）选到了 X：相当于从剩下 n-1 个人中再选 k-1 个 => C(n-1, k-1)
     *     2）没选到 X：从剩下 n-1 人中选 k 个 => C(n-1, k)
     *   两类情况不重不漏，因此：
     *       C(n, k) = C(n-1, k-1) + C(n-1, k)
     */
}

// 2. 范德蒙德公式：sum_{i=0}^{n} C(r, i) C(s, n-i) = C(r+s, n)
void demo_vandermonde_identity() {
    cout << "=== Vandermonde identity: sum_i C(r, i) * C(s, n-i) = C(r+s, n) ===\n";
    // 随便枚举几组 (r, s, n)
    for (int r = 0; r <= 6; ++r) {
        for (int s = 0; s <= 6; ++s) {
            int maxN = r + s;
            for (int n = 0; n <= maxN; ++n) {
                long long lhs = 0;
                for (int i = 0; i <= n; ++i) {
                    lhs += C(r, i) * C(s, n - i);
                }
                long long rhs = C(r + s, n);
                cout << "r=" << r << ", s=" << s << ", n=" << n << " : "
                     << "sum_i C(" << r << ",i)*C(" << s << "," << n << "-i) = " << lhs << ", C(" << r + s << "," << n
                     << ") = " << rhs << (lhs == rhs ? "  [OK]\n" : "  [MISMATCH]\n");
            }
        }
    }
    cout << "\n";

    /*
     * 组合解释（中文）：
     *   有两堆人：
     *       第一堆 r 个，第二堆 s 个。
     *   现在要从 r+s 个人中选 n 个。
     *   一方面：直接选 => C(r+s, n) 种。
     *   另一方面：按“从第一堆选了多少个 i”来分类：
     *       若从第一堆选 i 个，则从第二堆必须选 n-i 个 => C(r, i) * C(s, n-i)
     *   把所有可能的 i 累加，就得到左边：
     *       sum_{i=0}^{n} C(r, i) * C(s, n-i)
     *   两种计数方式是同一个事件的不同分类，因此两者相等。
     */
}

// 3. Hockey-stick identity：∑_{m=t}^{n} C(m, t) = C(n+1, t+1)
void demo_hockey_stick_identity() {
    cout << "=== Hockey-stick identity: sum_{m=t}^{n} C(m, t) = C(n+1, t+1) ===\n";
    for (int t = 0; t <= 6; ++t) {
        for (int n = t; n <= 10; ++n) {
            long long lhs = 0;
            for (int m = t; m <= n; ++m) {
                lhs += C(m, t);
            }
            long long rhs = C(n + 1, t + 1);
            cout << "t=" << t << ", n=" << n << " : "
                 << "sum_{m=" << t << "}^" << n << " C(m," << t << ") = " << lhs << ", C(" << n + 1 << "," << t + 1
                 << ") = " << rhs << (lhs == rhs ? "  [OK]\n" : "  [MISMATCH]\n");
        }
    }
    cout << "\n";

    /*
     * 证明思路一（用帕斯卡公式做“望远镜和”）：
     *   利用 Pascal：C(m, t) = C(m+1, t+1) - C(m, t+1)
     *   对 m = t..n 求和：
     *       ∑_{m=t}^{n} C(m, t)
     *     = ∑_{m=t}^{n} [C(m+1, t+1) - C(m, t+1)]
     *     = (C(t+1, t+1) + C(t+2, t+1) + ... + C(n+1, t+1))
     *       - (C(t, t+1) + C(t+1, t+1) + ... + C(n, t+1))
     *     右边是一个“错位相减”的望远镜和，全部抵消，只剩下 C(n+1, t+1)，
     *     而 C(t, t+1)=0。
     *
     * 证明思路二（组合解释）：
     *   你可以把 C(m, t) 看成：从前 m 个元素里选 t 个，
     *   而 C(n+1, t+1) 是从 n+1 个元素里选 t+1 个。
     *   然后按“选到的最大元素是哪一个”来分类，也可以得到同样的恒等式。
     */
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_combinations();

    // 你可以按需注释/取消注释下面这些 demo 调用。
    demo_print_combinations(10); // 打印一小部分 C(n,k)
    demo_pascal_identity(10); // 验证 Pascal 公式
    demo_vandermonde_identity(); // 验证 Vandermonde 公式
    demo_hockey_stick_identity(); // 验证 Hockey-stick 恒等式

    return 0;
}

/*

1. 帕斯卡公式（Pascal identity）
   C(n, k) = C(n-1, k-1) + C(n-1, k)

2. 范德蒙德公式（Vandermonde identity）
   ∑_{i=0}^{n} C(r, i) * C(s, n-i) = C(r+s, n)

3. Hockey-stick identity
   ∑_{m=t}^{n} C(m, t) = C(n+1, t+1)
*/
