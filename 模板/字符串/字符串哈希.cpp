//
// Created by 123 on 25-6-30.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

/*
下面的模板大概就是先取随机数MOD和BASE
创建n+1的数组
H里面的转移每个乘前一个和你的字符串的每个char
query传入r,l参数
H[r] - H[l - 1] * P[r - l + 1]
如果一样，两个H肯定一样，r-l+1也一样
*/

// 注意是 1-index 的，记得+1,-1

// 字符串哈希模板开始

// 两个都是后缀哈希
// query_rev_on_reversed 就是 区间[l, r]的哈希，不过是正着计算的
// query_rev_sub 是区间[l, r]的哈希，并且反转了。（可以理解为[r,l])

mt19937 rng(random_device{}());

int rnd(long long x, long long y) { return uniform_int_distribution<int>(x, y)(rng); }

long long MOD = 1e18 + rnd(0, 1e9);
int BASE = 233 + rnd(0, 1e3);

struct HashSeq {
    int n;
    vector<__int128> P, H, HR;

    HashSeq(string s) {
        n = s.size();
        P.resize(n + 1);
        P[0] = 1;
        for (int i = 1; i <= n; i++)
            P[i] = P[i - 1] * BASE % MOD;

        H.resize(n + 1);
        H[0] = 0;
        for (int i = 1; i <= n; i++)
            H[i] = (H[i - 1] * BASE + (s[i - 1] ^ 7)) % MOD;

        HR.resize(n + 1);
        HR[0] = 0;
        for (int i = 1; i <= n; i++) {
            HR[i] = (HR[i - 1] * BASE + (s[n - i] ^ 7)) % MOD;
        }
    }

    long long query(int l, int r) const {
        if (l > r)
            return 0;
        __int128 res = (H[r] - (H[l - 1] * P[r - l + 1]) % (__int128) MOD);
        long long ans = (long long) ((res + (__int128) MOD) % (__int128) MOD);
        return ans;
    }

    long long query_rev_on_reversed(int l, int r) const {
        if (l > r)
            return 0;
        __int128 res = (HR[r] - (HR[l - 1] * P[r - l + 1]) % (__int128) MOD);
        return (long long) ((res + (__int128) MOD) % (__int128) MOD);
    }

    long long query_rev_sub(int l, int r) const {
        if (l > r)
            return 0;
        int L = n - r + 1;
        int R = n - l + 1;
        __int128 res = (HR[R] - (HR[L - 1] * P[R - L + 1]) % (__int128) MOD);
        return (long long) ((res + (__int128) MOD) % (__int128) MOD);
    }
};

// 字符串哈希模板结束

void example(string s, string target) {
    int n = s.size();
    HashSeq hs(s);
    // 求 w 在 s 中出现的所有开头下标
    auto gao = [&](string w) {
        int len = w.size();
        HashSeq tmp(w);
        // 目标string
        long long goal = tmp.query(1, len);
        vector<int> pos;
        for (int i = 1; i + len - 1 <= n; i++) {
            if (len == 0 || hs.query(i, i + len - 1) == goal)
                pos.push_back(i);
        }
        return pos;
    };
    auto all_indices = gao(target);
}

// 3031题目
class Solution {
public:
    int minimumTimeToInitialState(string word, int K) {
        int n = word.size();
        // 随机模数和基数，防止被 hack
        srand(time(nullptr));
        int MOD = 998244353 + rand() % 10007;
        int BASE = 33 + rand() % 233;

        // 字符串哈希模板开始
        long long P[n + 1];
        P[0] = 1;
        for (int i = 1; i <= n; i++)
            P[i] = P[i - 1] * BASE % MOD;

        long long H[n + 1];
        H[0] = 0;
        for (int i = 1; i <= n; i++)
            H[i] = (H[i - 1] * BASE + word[i - 1] - 'a') % MOD;

        auto query = [&](int L, int R) { return (H[R] - H[L - 1] * P[R - L + 1] % MOD + MOD) % MOD; };
        // 字符串哈希模板结束

        for (int i = K; i < n; i += K) {
            int len = n - i;
            // 判断从第 i + 1 个字符开始的后缀是不是原字符串的前缀
            if (query(1, len) == query(i + 1, n))
                return i / K;
        }
        // 答案的上界
        return (n + K - 1) / K;
    }
};
