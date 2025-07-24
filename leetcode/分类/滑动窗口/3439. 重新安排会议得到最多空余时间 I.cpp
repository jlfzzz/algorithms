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

using namespace std;

class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int> &startTime, vector<int> &endTime) {
        int n = startTime.size();

        // 处理没有事件的边界情况
        if (n == 0) {
            return eventTime;
        }

        // 初始的 sum 包含第一个空闲时隙 (事件0开始前的时间)
        int sum = startTime[0];
        int ans = 0;

        // 遍历事件 1 到 n-1
        for (int i = 1; i < n; i++) {
            // 加上第 i 个空闲时隙的持续时间 (事件 i 开始前，事件 i-1 结束后)
            sum += startTime[i] - endTime[i - 1];

            // 如果窗口还未包含 k+1 个时隙 (即累加的时隙数不足 k+1 个)，则继续
            // 当 i=k 时，sum 包含了 0 到 k 共 k+1 个时隙
            if (i < k) continue;

            // 更新最大总空闲时间
            // 当 i=k 时, sum 代表了时隙 0 到 k 的总和.
            // 当 i>k 时, 在上一轮迭代结束时，sum 代表了时隙 [i-1-k, i-1] 的总和。
            // 这一轮加上了时隙 i，所以在执行 ans = max(ans, sum) 时，
            // sum 代表了时隙 [i-k, i] 的总和。
            ans = max(ans, sum);

            // -------- 开始重写的部分 --------
            // 计算需要从 sum 中移除的那个空闲时隙 (索引为 i - k) 的持续时间，
            // 以便在下一次迭代开始时，sum 代表 [i+1-k, i] 的总和。
            int index_of_slot_to_remove = i - k;
            int time_slot_duration_to_remove;

            if (index_of_slot_to_remove == 0) {
                // 如果要移除的是第 0 个时隙，其持续时间是 startTime[0]
                time_slot_duration_to_remove = startTime[0];
            } else {
                // 如果要移除的是第 j (j>0) 个时隙，其持续时间是 startTime[j] - endTime[j-1]
                // 这里 j = index_of_slot_to_remove
                // 注意 C++ 数组索引是从 0 开始的，所以前一个事件的结束时间索引是 index_of_slot_to_remove - 1
                time_slot_duration_to_remove = startTime[index_of_slot_to_remove] - endTime[index_of_slot_to_remove - 1];
            }

            // 从 sum 中减去该时隙的持续时间
            sum -= time_slot_duration_to_remove;
            // -------- 结束重写的部分 --------
        }

        // 循环结束后, ans 保存了所有结束于时隙 n-1 或之前的窗口的最大和
        // sum 保存了最后一个计算的窗口 [n-k, n-1] 的和
        // 现在需要考虑包含最后一个时隙 (时隙 n, 即最后一个事件结束后到 eventTime 的时间) 的窗口 [n-k, n]
        sum += eventTime - endTime[n - 1]; // 加上最后一个时隙的持续时间

        // 返回 ans 和 最后一个窗口的和 中的较大值
        return max(ans, sum);
    }
};