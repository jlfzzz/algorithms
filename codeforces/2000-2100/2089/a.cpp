#include <algorithm> // std::sort, for a potential alternative generation
#include <cmath>
#include <iostream>
#include <numeric> // std::iota, for a potential alternative generation
#include <vector>


// 使用 using namespace std; 在竞赛编程中很常见，但在大型项目中不推荐
using namespace std;

/**
 * @brief 检查一个整数是否为质数（素数）。
 * * @param x 要检查的整数。
 * @return 如果 x 是质数，返回 true；否则返回 false。
 */
bool isPrime(int x) {
    // 1 和所有小于等于1的数都不是质数
    if (x <= 1) {
        return false;
    }
    // 通过试除法检查因子，只需检查到 sqrt(x)
    for (int i = 2; i * i <= x; ++i) {
        // 如果能被整除，则不是质数
        if (x % i == 0) {
            return false;
        }
    }
    // 如果没有找到任何因子，则是质数
    return true;
}

/**
 * @brief 根据给定的 n 和一个质数 p 生成排列。
 * * @param n 排列的大小 (数字从 1 到 n)。
 * @param p 用作构造起点的质数。
 * @return 返回一个 vector<int>，其中包含构造出的序列。
 * 注意：这个函数可能会生成超过 n 个元素，但主函数只会使用前 n 个。
 */
vector<int> generateSol(int n, int p) {
    vector<int> ans;
    // 首先将质数 p 放入序列
    ans.push_back(p);

    // 以 p为中心，交替向两边扩展
    // p-1, p+1, p-2, p+2, ...
    for (int i = 1; i <= n; ++i) {
        // 添加 p-i, 如果它在 [1, n] 范围内
        if (p - i > 0) {
            ans.push_back(p - i);
        }
        // 添加 p+i, 如果它在 [1, n] 范围内
        if (p + i <= n) {
            ans.push_back(p + i);
        }
    }
    return ans;
}

int main() {
    // 提高cin/cout的效率，在竞赛编程中常用
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; // 测试用例的数量
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> ans;
        int p = 0;

        // 从 n/2 开始向外寻找最近的质数
        for (int x = 0;; ++x) {
            // 检查 n/2 - x
            if (n / 2 - x > 0 && isPrime(n / 2 - x)) {
                p = n / 2 - x;
                break;
            }
            // 检查 n/2 + x
            if (n / 2 + x <= n && isPrime(n / 2 + x)) {
                p = n / 2 + x;
                break;
            }
        }

        // 使用找到的质数 p 生成解
        ans = generateSol(n, p);

        // 打印结果的前 n 个元素
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
