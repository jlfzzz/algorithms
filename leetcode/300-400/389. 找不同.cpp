#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    char findTheDifference(string s, string t) {
        vector<int> cnt(26, 0);
        for (char ch : s) {
            cnt[ch - 'a']++;
        }
        for (char ch : t) {
            cnt[ch - 'a']--;
            if (cnt[ch - 'a'] < 0) {
                return ch;
            }
        }
        return ' ';
    }
};

/*
将字符串 s 中每个字符的 ASCII 码的值求和
*/
class Solution2 {
public:
    char findTheDifference(string s, string t) {
        int as = 0, at = 0;
        for (char ch : s) {
            as += ch;
        }
        for (char ch : t) {
            at += ch;
        }
        return at - as;
    }
};

class Solution3 {
public:
    char findTheDifference(string s, string t) {
        int ret = 0;
        for (char ch : s) {
            ret ^= ch;
        }
        for (char ch : t) {
            ret ^= ch;
        }
        return ret;
    }
};

/*
这段代码使用 异或（XOR）运算 来找出字符串 t 比字符串 s 多出的那个字符。它的核心思想是利用了异或运算的两个关键特性：

异或运算（XOR）的特性
相同数异或结果为 0：

a ^ a = 0

任何数与 0 异或结果不变：

a ^ 0 = a

异或满足交换律和结合律：

a ^ b ^ a = (a ^ a) ^ b = 0 ^ b = b

代码执行流程
初始化 ret = 0：

作为异或运算的初始值。

第一次遍历字符串 s：

将 s 中所有字符依次与 ret 异或：

cpp
复制
for (char ch : s) ret ^= ch;
相当于计算 ret = s[0] ^ s[1] ^ ... ^ s[n-1]。

第二次遍历字符串 t：

将 t 中所有字符依次与 ret 异或：

cpp
复制
for (char ch : t) ret ^= ch;
由于 t 比 s 多一个字符（假设 t 是 s 的随机重排并添加一个字符），异或运算后：

s 和 t 中相同的字符会两两抵消（因为 a ^ a = 0）。

最终 ret 的值就是多出的那个字符（因为 0 ^ b = b）。

举例说明
假设：

s = "abc" → s 的异或结果：'a' ^ 'b' ^ 'c'。

t = "cbaa" → t 比 s 多一个 'a'。

运算过程：

遍历 s：

ret = 0 ^ 'a' ^ 'b' ^ 'c'。

遍历 t：

ret = (0 ^ 'a' ^ 'b' ^ 'c') ^ 'c' ^ 'b' ^ 'a' ^ 'a'。

交换律整理：ret = 0 ^ ('a' ^ 'a') ^ ('b' ^ 'b') ^ ('c' ^ 'c') ^ 'a'。

相同字符抵消：ret = 0 ^ 0 ^ 0 ^ 0 ^ 'a' = 'a'。

返回 'a'。

为什么能解决问题？
t 是 s 的随机重排 + 一个新增字符，因此：

s 和 t 中共有字符会成对出现，异或后结果为 0。

多出的字符会单独留下（因为异或 0 等于它本身）。

复杂度分析
时间复杂度：O(m + n)，其中 m 和 n 是 s 和 t 的长度（实际 n = m + 1）。

空间复杂度：O(1)，仅用了一个变量 ret。

适用场景
题目明确保证 t 是 s 的随机重排并恰好多一个字符。

如果可能有多个差异字符，此方法不适用（需改用哈希表统计）。


*/


