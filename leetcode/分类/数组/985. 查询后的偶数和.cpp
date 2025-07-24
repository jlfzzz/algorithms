#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int> &nums, vector<vector<int>> &queries) {
        int even_sum = 0;
        // 预处理计算初始偶数和
        for (int num : nums) {
            if (num % 2 == 0) {
                even_sum += num;
            }
        }

        vector<int> result;
        result.reserve(queries.size()); // 预分配空间提高效率

        for (const auto &query : queries) {
            int val = query[0];
            int index = query[1];
            int &num = nums[index]; // 使用引用避免重复访问

            // 先移除原数对偶数和的影响（如果是偶数）
            if (num % 2 == 0) {
                even_sum -= num;
            }

            // 更新数值
            num += val;

            // 检查更新后的数是否为偶数
            if (num % 2 == 0) {
                even_sum += num;
            }

            result.push_back(even_sum);
        }

        return result;
    }
};