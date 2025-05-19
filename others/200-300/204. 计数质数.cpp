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

using namespace std;

class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) {
            return 0; // 小于等于 2 没有质数 (严格小于 n)
        }

        // 创建一个布尔向量，标记数字是否为质数
        // isPrime[i] = true 表示 i 可能是质数
        // isPrime[i] = false 表示 i 是合数
        vector<bool> isPrime(n, true);
        isPrime[0] = isPrime[1] = false; // 0 和 1 不是质数

        // 埃拉托斯特尼筛法
        // 只需要检查到 sqrt(n) 即可
        // 因为如果 i 是合数，它必然有一个小于或等于 sqrt(n) 的质因子
        for (int p = 2; p * p < n; ++p) {
            // 如果 isPrime[p] 仍然是 true，那么 p 是一个质数
            if (isPrime[p]) {
                // 将 p 的所有倍数（从 p*p 开始）标记为合数
                // 小于 p*p 的 p 的倍数已经被更小的质因子标记过了
                for (int i = p * p; i < n; i += p) {
                    isPrime[i] = false;
                }
            }
        }

        // 统计质数的数量
        int count = 0;
        for (int i = 2; i < n; ++i) {
            if (isPrime[i]) {
                count++;
            }
        }

        return count;
    }
};

class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) {
            return 0; // 小于等于 2 没有质数 (严格小于 n)
        }

        // 创建一个布尔向量，标记数字是否为质数
        // isPrime[i] = true 表示 i 可能是质数
        // isPrime[i] = false 表示 i 是合数
        vector<bool> isPrime(n, true);
        isPrime[0] = isPrime[1] = false; // 0 和 1 不是质数

        // 埃拉托斯特尼筛法
        // 只需要检查到 sqrt(n) 即可
        // 因为如果 i 是合数，它必然有一个小于或等于 sqrt(n) 的质因子
        for (int p = 2; p * p < n; ++p) {
            // 如果 isPrime[p] 仍然是 true，那么 p 是一个质数
            if (isPrime[p]) {
                // 将 p 的所有倍数（从 p*p 开始）标记为合数
                // 小于 p*p 的 p 的倍数已经被更小的质因子标记过了
                for (int i = p * p; i < n; i += p) {
                    isPrime[i] = false;
                }
            }
        }

        // 统计质数的数量
        int count = 0;
        for (int i = 2; i < n; ++i) {
            if (isPrime[i]) {
                count++;
            }
        }

        return count;
    }
};