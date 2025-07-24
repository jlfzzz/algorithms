#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int maxLength(vector<string> &arr) {
        int n = arr.size();
        int ans = 0;
        string curr;
        int mask1 = 0; // 记录当前已选字符的位掩码

        auto dfs = [&](this auto &&self, int index) -> void {
            if (index == n) {
                ans = max(ans, (int)curr.size());
                return;
            }

            // 不选当前字符串
            self(index + 1);

            // 选当前字符串（需检查是否有重复字符）
            int mask2 = 0;
            bool valid = true;
            for (char c : arr[index]) {
                if (mask2 & (1 << (c - 'a'))) { // 当前字符串内部有重复字符
                    valid = false;
                    break;
                }
                mask2 |= (1 << (c - 'a'));
            }

            if (valid && !(mask1 & mask2)) { // 当前字符串和已选字符无重复
                curr += arr[index];
                mask1 ^= mask2; // 更新掩码
                self(index + 1);
                curr.erase(curr.size() - arr[index].size()); // 回溯
                mask1 ^= mask2; // 恢复掩码
            }
            };

        dfs(0);
        return ans;
    }
};