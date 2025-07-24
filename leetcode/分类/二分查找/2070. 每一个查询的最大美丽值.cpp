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
    vector<int> maximumBeauty(vector<vector<int>> &items, vector<int> &queries) {
        int n = queries.size();
        vector<int> ans(n);
        int m = items.size();

        // 转换为 pair 方便处理
        vector<pair<int, int>> itemPairs(m);
        for (int i = 0; i < m; i++) {
            itemPairs[i] = { items[i][0], items[i][1] }; // {price, beauty}
        }

        // 1. 按价格排序
        sort(itemPairs.begin(), itemPairs.end());

        // 2. 预处理最大美丽度
        // itemPairs[i].second 将存储价格 <= itemPairs[i].first 的物品的最大美丽度
        int max_beauty_so_far = 0;
        for (int i = 0; i < m; i++) {
            max_beauty_so_far = max(max_beauty_so_far, itemPairs[i].second);
            itemPairs[i].second = max_beauty_so_far;
        }

        // 3. 处理查询
        for (int i = 0; i < n; i++) {
            int price = queries[i];

            // 查找第一个价格 > price 的物品
            // 使用 lambda 定义比较规则：比较查询价格 price 和物品的价格 item.first
            auto it = upper_bound(itemPairs.begin(), itemPairs.end(), price,
                [](int p_val, const pair<int, int> &item) {
                    // 如果 p_val < item.first 返回 true
                    return p_val < item.first;
                });

            if (it == itemPairs.begin()) {
                // 所有物品价格都 > price，没有符合条件的
                ans[i] = 0;
            } else {
                // it 指向第一个价格 > price 的物品
                // prev(it) 指向价格 <= price 的最右边的物品
                // 其 second 值即为价格 <= price 的物品中的最大美丽度（已预处理）
                ans[i] = prev(it)->second;
            }
        }

        return ans;
    }
};