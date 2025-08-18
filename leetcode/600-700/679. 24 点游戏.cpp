#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solution {
private:
    const double EPS = 1e-6;

    // 递归尝试所有可能的运算组合
    bool solve(vector<double> &nums) {
        int n = nums.size();
        if (n == 1) {
            return abs(nums[0] - 24.0) < EPS;
        }

        // 选择两个数进行运算
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double a = nums[i], b = nums[j];

                // 构造新的数组，移除选中的两个数
                vector<double> next;
                for (int k = 0; k < n; k++) {
                    if (k != i && k != j) {
                        next.push_back(nums[k]);
                    }
                }

                // 尝试四种运算符
                vector<double> operations = {a + b, a - b, b - a, a * b};

                // 除法需要特别处理，避免除零
                if (abs(b) > EPS)
                    operations.push_back(a / b);
                if (abs(a) > EPS)
                    operations.push_back(b / a);

                for (double result: operations) {
                    next.push_back(result);
                    if (solve(next))
                        return true;
                    next.pop_back();
                }
            }
        }

        return false;
    }

public:
    bool judgePoint24(vector<int> &cards) {
        vector<double> nums(cards.begin(), cards.end());
        sort(nums.begin(), nums.end());

        // 尝试所有排列
        do {
            if (solve(nums))
                return true;
        } while (next_permutation(nums.begin(), nums.end()));

        return false;
    }
};
