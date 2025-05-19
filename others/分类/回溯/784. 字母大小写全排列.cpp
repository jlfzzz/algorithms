#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/*
A 的Ascii 值为65（十进制） 二进制为  01000010
Z 的Ascii 值为90（十进制） 二进制为  01011010
而32的二进制值为                     00100000
异或运算后正好加入了32.。所以可以从大写转小写，从小转大异或运算去掉1 也就可以了
*/

class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> ans;
        int n = s.size();

        auto dfs = [&](this auto &&dfs, int index) -> void {
            if (index == n) {
                ans.push_back(s);
                return;
            }

            if (isdigit(s[index])) {
                dfs(index + 1); // 数字直接跳过
            } else {
                // 切换大小写
                s[index] ^= 32;
                dfs(index + 1);
                // 切换回来
                s[index] ^= 32;
                dfs(index + 1);
            }
            };

        dfs(0);
        return ans;
    }
};