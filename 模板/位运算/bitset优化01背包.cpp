#include <bits/stdc++.h>
#include <bitset>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
const ll MOD2 = 4611686018427387847;

// lc3181
// bitset 第 i 位如果是1，代表 value i 是 true
// 类似0-1背包dp[i]=true
// 当前是x，更新0-1背包dp数组时候，首先题目要求只能与更新小于当前x的值
// 会把所有是true的索引k,然后把k+x也更新会true
// 等价于bitset的x右边的所有位都左移x位，再或一下原来的bitset
class Solution {
public:
    int maxTotalReward(vector<int> &rewardValues) {
        ranges::sort(rewardValues);
        rewardValues.erase(unique(rewardValues.begin(), rewardValues.end()), rewardValues.end());

        bitset<100000> f{1};
        for (int v: rewardValues) {
            int shift = f.size() - v;
            // 左移 shift 再右移 shift，把所有 >= v 的比特位置 0
            // f |= f << shift >> shift << v;
            f |= f << shift >> (shift - v); // 简化上式
        }
        for (int i = rewardValues.back() * 2 - 1;; i--) {
            if (f.test(i)) {
                return i;
            }
        }
    }
};
