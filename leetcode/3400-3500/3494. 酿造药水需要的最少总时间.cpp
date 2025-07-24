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
    long long minTime(vector<int> &skill, vector<int> &mana) {
        int n = skill.size();
        vector<long long> last_finish(n); // 第 i 名巫师完成上一瓶药水的时间
        for (int m : mana) {
            // 按题意模拟
            long long sum_t = 0;
            for (int i = 0; i < n; i++) {
                sum_t = max(sum_t, last_finish[i]) + skill[i] * m;
            }
            // 倒推：如果酿造药水的过程中没有停顿，那么 lastFinish[i] 应该是多少
            last_finish[n - 1] = sum_t;
            for (int i = n - 2; i >= 0; i--) {
                last_finish[i] = last_finish[i + 1] - skill[i + 1] * m;
            }
        }
        return last_finish[n - 1];
    }
};