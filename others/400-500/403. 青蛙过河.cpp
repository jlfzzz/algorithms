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

using namespace std;

class Solution {
public:
    bool canCross(vector<int> &stones) {
        int n = stones.size();
        // 处理特殊情况
        if (n == 0) return true; // 没有石头？（按题意应该至少有起点0）
        // 检查起点
        if (stones[0] != 0) return false; // 起点必须是0
        // 检查第一步的可行性
        if (n > 1 && stones[1] != 1) return false; // 第二块石头必须在位置1
        // 如果只有一块石头（在0），已经成功（或者说无法跳）
        if (n == 1) return true; // 只有一块石头在0，已经算到达（虽然没跳）


        // 使用哈希集合快速查找石头是否存在
        unordered_set<int> stone_set(stones.begin(), stones.end());

        // dp[stone_pos] 存储一个集合，包含所有能够跳到 stone_pos 的“最后一步跳跃距离”
        unordered_map<int, unordered_set<int>> dp;

        // 初始化：
        dp[0].insert(0); // 标记起点可以出发，下一步跳1
        dp[1].insert(1); // 到达石头 1 (位置1) 的最后一步跳跃距离是 1

        // 遍历所有石头（可以从索引1开始，因为0和1已经初始化）
        for (int i = 1; i < n; ++i) {
            int current_stone = stones[i];
            // 遍历所有能够到达 current_stone 的上一步跳跃距离 k
            // 复制一份避免迭代时修改
            unordered_set<int> current_jumps = dp[current_stone];
            for (int k : current_jumps) {
                // 尝试三种可能的下一步跳跃距离: k-1, k, k+1
                for (int next_jump = k - 1; next_jump <= k + 1; ++next_jump) {
                    // 跳跃距离必须大于 0
                    if (next_jump > 0) {
                        int next_stone_pos = current_stone + next_jump;
                        // 检查目标位置是否有石头
                        if (stone_set.count(next_stone_pos)) {
                            // 如果能到达最后一块石头，直接返回true
                            if (next_stone_pos == stones[n - 1]) {
                                return true;
                            }
                            // 将这个有效的 next_jump 添加到目标石头的可达跳跃距离集合中
                            dp[next_stone_pos].insert(next_jump);
                        }
                    }
                }
            }
        }

        // 如果循环结束，检查最后一个石头是否被记录过可达跳跃距离
        // （实际上上面的循环中已经提前返回了，这里是备用检查）
        return !dp[stones[n - 1]].empty();
    }
};