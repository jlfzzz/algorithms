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
#include <queue>
#include <cstring>
#include <array> 
#include <bitset>

using namespace std;

class Solution {
    static constexpr int BIT_WIDTH = 7;

    // 421. 数组中两个数的最大异或值
    // 改成两个数组的最大异或值，做法是类似的，仍然可以用【试填法】解决
    int findMaximumXOR(vector<int> &a, vector<int> &b) {
        int ans = 0, mask = 0;
        vector<int> seen(1 << BIT_WIDTH);
        for (int i = BIT_WIDTH - 1; i >= 0; i--) { // 从最高位开始枚举
            mask |= 1 << i;
            int new_ans = ans | (1 << i); // 这个比特位可以是 1 吗？
            ranges::fill(seen, false);
            for (int x : a) {
                seen[x & mask] = true; // 低于 i 的比特位置为 0
            }
            for (int x : b) {
                x &= mask; // 低于 i 的比特位置为 0
                if (seen[new_ans ^ x]) {
                    ans = new_ans; // 这个比特位可以是 1
                    break;
                }
            }
        }
        return ans;
    }

public:
    int maxValue(vector<int> &nums, int k) {
        const int MX = 1 << BIT_WIDTH;
        int n = nums.size();
        int k2 = min(k, BIT_WIDTH); // 至多选 k2 个数

        vector<array<int, MX>> suf(n - k + 1);
        vector<array<int, MX>> f(k2 + 1);
        f[0][0] = true;
        int max_i[MX]{}, cnt[MX]{};
        for (int i = n - 1; i >= k; i--) {
            int v = nums[i];
            // 注意当 i 比较大的时候，循环次数应和 i 有关，因为更大的 j，对应的 f[j] 全为 false
            for (int j = min(k2 - 1, n - 1 - i); j >= 0; j--) {
                for (int x = 0; x < MX; x++) {
                    if (f[j][x]) {
                        f[j + 1][x | v] = true;
                    }
                }
            }
            if (i <= n - k) {
                suf[i] = f[k2];
            }
            // 枚举 v 的超集
            for (int s = v; s < MX; s = (s + 1) | v) {
                if (++cnt[s] == k) {
                    // 从 n-1 开始遍历，至少要遍历到 i 才有可能找到 k 个数 OR 等于 s
                    max_i[s] = i;
                }
            }
        }

        int ans = 0;
        vector<array<int, MX>> pre(k2 + 1);
        pre[0][0] = true;
        int min_i[MX];
        ranges::fill(min_i, INT_MAX);
        ranges::fill(cnt, 0);
        for (int i = 0; i < n - k; i++) {
            int v = nums[i];
            for (int j = min(k2 - 1, i); j >= 0; j--) {
                for (int x = 0; x < MX; x++) {
                    if (pre[j][x]) {
                        pre[j + 1][x | v] = true;
                    }
                }
            }
            // 枚举 v 的超集
            for (int s = v; s < MX; s = (s + 1) | v) {
                if (++cnt[s] == k) {
                    // 从 0 开始遍历，至少要遍历到 i 才有可能找到 k 个数 OR 等于 s
                    min_i[s] = i;
                }
            }
            if (i < k - 1) {
                continue;
            }
            vector<int> a, b;
            for (int x = 0; x < MX; x++) {
                if (pre[k2][x] && min_i[x] <= i) {
                    a.push_back(x);
                }
                if (suf[i + 1][x] && max_i[x] > i) {
                    b.push_back(x);
                }
            }
            ans = max(ans, findMaximumXOR(a, b));
            if (ans == MX - 1) {
                return ans;
            }
        }
        return ans;
    }
};