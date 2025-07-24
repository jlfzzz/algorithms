#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isAdditiveNumber(string num) {
        int n = num.size();
        for (int i = 1; i <= n / 2; i++) {
            for (int j = 1; j <= (n - i) / 2; j++) {
                string firstStr = num.substr(0, i);
                string secondStr = num.substr(i, j);
                // 检查前导零
                if ((firstStr.size() > 1 && firstStr[0] == '0') ||
                    (secondStr.size() > 1 && secondStr[0] == '0')) {
                    continue;
                }
                long long first = stoll(firstStr);
                long long second = stoll(secondStr);
                if (dfs(first, second, i + j, num)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool dfs(long long first, long long second, int index, string &num) {
        if (index == num.size()) {
            return true; // 至少有三个数字已在主函数中验证
        }
        long long target = first + second;
        string targetStr = to_string(target);
        if (num.substr(index, targetStr.size()) != targetStr) {
            return false;
        }
        return dfs(second, target, index + targetStr.size(), num);
    }
};