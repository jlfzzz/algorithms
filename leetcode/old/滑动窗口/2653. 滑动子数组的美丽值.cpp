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

using namespace std;

// 别用insert，3超时

class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int> &nums, int k, int x) {
        vector<int> bucket(101, 0);
        vector<int> ans;
        int n = nums.size();

        int left = 0;
        for (int right = 0; right < n; right++) {
            int number = nums[right];
            bucket[number + 50]++;

            if (right - left + 1 == k) {
                int target = x;
                for (int j = 0; j < 51; j++) {
                    target -= bucket[j];
                    if (target <= 0) {
                        ans.emplace_back(j - 50);
                        break;
                    }
                }

                if (target > 0) {
                    ans.emplace_back(0);
                }

                bucket[nums[left++] + 50]--;
            }
        }

        return ans;
    }
};



class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int> &nums, int k, int x) {
        vector<int> ans;
        int n = nums.size();
        map<int, int> count; // 使用 map 存储窗口内数字及其频率
        int left = 0;

        for (int right = 0; right < n; ++right) {
            // 将右边界元素加入窗口
            count[nums[right]]++;

            // 当窗口大小达到 k 时，计算 beauty 并移除左边界元素
            if (right - left + 1 == k) {
                int current_x = 0;
                int beauty = 0; // 默认为 0

                // 遍历 map 查找第 x 小的负数
                // map 会按键（数字）自动排序
                for (auto const &[num, freq] : count) {
                    // 如果当前数字已经是非负数，则后续数字更大，
                    // 且第 x 小的元素肯定不是负数（或已找到），停止查找
                    if (num >= 0) {
                        break;
                    }
                    current_x += freq; // 累加当前负数的频率
                    // 如果累积计数达到或超过 x，则当前负数就是第 x 小的元素
                    if (current_x >= x) {
                        beauty = num;
                        break; // 找到了，退出循环
                    }
                }

                ans.push_back(beauty); // 将计算得到的 beauty 加入结果

                // 将左边界元素移出窗口
                count[nums[left]]--;
                if (count[nums[left]] == 0) {
                    count.erase(nums[left]); // 如果频率变为 0，则从 map 中移除
                }
                left++; // 窗口向右滑动
            }
        }

        return ans;
    }
};



class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        vector<int> ans;
        int n = nums.size();
        vector<int> path;
        int left = 0;

        for (int right = 0; right < n; right++) {
            int number = nums[right];
            int i = 0;
            int size = path.size();
            while (i < size && path[i] < number) {
                i++;
            }
            path.insert(path.begin() + i, number);

            if (right - left + 1 == k) {
                if (path[x - 1] < 0) {
                    ans.emplace_back(path[x - 1]);
                } else {
                    ans.emplace_back(0);
                }

                int deleted = nums[left];
                int j = 0;
                while (path[j] != deleted) {
                    j++;
                }
                path.erase(path.begin() + j);
                left++;
            }
        }

        return ans;
    }
};