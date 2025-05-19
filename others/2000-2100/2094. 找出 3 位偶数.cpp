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
#include <set>

using namespace std;

class Solution {
public:
    vector<int> findEvenNumbers(vector<int> &digits) {
        int cnt[10]{};
        for (int d : digits) {
            cnt[d]++;
        }

        vector<int> ans;
        for (int i = 100; i < 1000; i += 2) { // 枚举所有三位数偶数 i
            int c[10]{};
            bool ok = true;
            for (int x = i; x > 0; x /= 10) { // 枚举 i 的每一位 d
                int d = x % 10;
                // 如果 i 中 d 的个数比 digits 中的还多，那么 i 无法由 digits 中的数字组成
                if (++c[d] > cnt[d]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};