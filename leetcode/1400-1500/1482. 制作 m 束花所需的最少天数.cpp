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
    int minDays(vector<int> &bloomDay, int m, int k) {
        int n = bloomDay.size();
        if (n / k < m) return -1;

        int hi = INT_MAX / 2;
        int lo = 1;
        int ans = hi;

        auto check = [&](int days) -> bool {
            int flower = 0;
            int i = 0;
            int left = 0;
            while (1) {


                while (i < n && bloomDay[i] <= days) {
                    i++;
                }
                flower += (i - left) / k;

                if (i == n) break;
                i++;
                left = i;
            }

            return flower >= m;
            };

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (check(mid)) {
                hi = mid;
                ans = mid;
            } else {
                lo = mid + 1;
            }
        }

        return hi != INT_MAX / 2 ? hi : -1;
    }
};