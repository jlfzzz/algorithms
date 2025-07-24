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
#include <bitset>
#include <stack>

using namespace std;

class Solution {
public:
    int earliestSecondToMarkIndices(vector<int> &nums, vector<int> &changeIndices) {
        int n = nums.size(), m = changeIndices.size();
        if (n > m) return -1;

        vector<int> done(n); // 避免反复创建和初始化数组
        auto check = [&](int mx) -> bool {
            int exam = n, study = 0;
            for (int i = mx - 1; i >= 0 && study <= i + 1; i--) { // 要复习的天数不能太多
                int idx = changeIndices[i] - 1;
                if (done[idx] != mx) {
                    done[idx] = mx;
                    exam--; // 考试
                    study += nums[idx]; // 需要复习的天数
                } else if (study) {
                    study--; // 复习
                }
            }
            return exam == 0 && study == 0; // 考完了并且复习完了
            };

        int left = n - 1, right = m + 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            (check(mid) ? right : left) = mid;
        }
        return right > m ? -1 : right;
    }
};