#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans; // 存储最终所有分割方案
        vector<string> path;      // 存储当前找到的一个分割路径
        int n = s.size();

        // 辅助函数：检查子串 s[start..end] 是否为回文串
        // 注意：直接传递索引比每次创建子串更高效
        auto isPalindrome = [&](int start, int end) -> bool {
            while (start < end) {
                if (s[start] != s[end]) {
                    return false;
                }
                start++;
                end--;
            }
            return true;
            };

        // DFS 函数，startIndex 表示当前尝试分割的起始位置
        // 使用 explicit object parameter 'self' 或 'dfs_ref' 代替 this auto&& 语法以提高清晰度
        function<void(int)> dfs =
            [&](int startIndex) -> void {
            // 基准条件：如果 startIndex 到达字符串末尾，说明找到了一个完整的分割方案
            if (startIndex == n) {
                ans.push_back(path); // 将当前路径添加到结果集中
                return;
            }

            // 尝试在 startIndex 后面的每个位置 i 进行切割
            for (int i = startIndex; i < n; ++i) {
                // 检查从 startIndex 到 i 的子串是否是回文串
                if (isPalindrome(startIndex, i)) {
                    // 如果是回文串，将其加入当前路径
                    path.push_back(s.substr(startIndex, i - startIndex + 1));

                    // 继续从 i+1 的位置向后搜索
                    dfs(i + 1); // 递归调用

                    // 回溯：撤销选择，将刚才加入的回文串从路径中移除
                    path.pop_back();
                }
                // 如果 s[startIndex..i] 不是回文串，继续增大 i 尝试更长的子串
            }
            };

        dfs(0); // 从索引 0 开始进行 DFS 搜索
        return ans;
    }
};










class Solution2 {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<int> partition;
        partition.emplace_back(0);
        //int start = 0;
        int n = s.size();

        auto check = [&](int start, int end) -> bool {
            for (int i = 0; i < (end - start) / 2; i++) {
                if (s[i + start] != s[end - i - 1])
                    return false;
            }
            return true;
            };



        auto dfs = [&](this auto &&dfs, int index) -> void {
            if (index == n) {
                int size = partition.size();
                bool flag = true;
                vector<string> temp;
                for (int i = 0; i < size; i++) {
                    if (i == size - 1) {
                        flag = check(partition[i], n);
                        temp.push_back(s.substr(partition[i], n - partition[i]));
                    } else {
                        flag = check(partition[i], partition[i + 1]);
                        temp.push_back(s.substr(partition[i], partition[i + 1] - partition[i]));
                    }
                    if (flag == false) break;
                }
                if (flag) {
                    ans.push_back(temp);
                }
                return;
            }

            dfs(index + 1);
            partition.emplace_back(index);
            dfs(index + 1);
            partition.pop_back();
            };
        dfs(1);
        return ans;
    }
};