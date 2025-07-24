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

#include <vector>       // 包含 vector 头文件
#include <numeric>      // 包含 numeric 头文件 (如果使用 partial_sum)
#include <algorithm>    // 包含 algorithm 头文件 (sort, upper_bound)
#include <vector>       // 重复包含，可以去掉一个

class Solution {
public:
    /**
     * @brief 计算满足和小于等于查询值的最长子序列长度。
     *
     * @param nums 整数数组。
     * @param queries 查询数组。
     * @return std::vector<int> 每个查询对应的最长子序列长度。
     */
    std::vector<int> answerQueries(std::vector<int> &nums, std::vector<int> &queries) {
        int n = nums.size();

        // 1. 对 nums 排序
        std::sort(nums.begin(), nums.end());

        // 2. 计算前缀和
        // prefix_sums[i] 存储 nums[0]...nums[i-1] 的和
        // 大小为 n+1, prefix_sums[0] = 0
        // 使用 long long 防止潜在的整数溢出，虽然此题约束下 int 应该足够
        std::vector<long long> prefix_sums(n + 1, 0LL);
        for (int i = 0; i < n; ++i) {
            prefix_sums[i + 1] = prefix_sums[i] + nums[i];
        }

        int m = queries.size();
        std::vector<int> answer(m);

        // 3. 处理每个查询
        for (int i = 0; i < m; ++i) {
            int q = queries[i];

            // 在前缀和数组中查找第一个 > q 的元素
            // 注意：需要将查询值 q 转换为 long long 进行比较，以匹配 prefix_sums 的类型
            auto it = std::upper_bound(prefix_sums.begin(), prefix_sums.end(), (long long)q);

            // upper_bound 返回指向第一个大于 q 的元素的迭代器。
            // 这个迭代器之前的元素个数（即迭代器距离起始位置的距离 - 1）
            // 就是和小于等于 q 的最大元素个数。
            // std::distance(prefix_sums.begin(), it) 得到的是索引 k，其中 prefix_sums[k] > q
            // 这意味着 prefix_sums[k-1] <= q，而 prefix_sums[k-1] 是前 k-1 个元素的和。
            // 所以，我们可以取 k-1 个元素。
            answer[i] = std::distance(prefix_sums.begin(), it) - 1;
        }

        return answer;
    }
};