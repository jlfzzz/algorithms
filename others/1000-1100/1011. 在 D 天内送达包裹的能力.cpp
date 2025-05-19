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

using namespace std;

class Solution {
public:
    int shipWithinDays(vector<int> &weights, int days) {
        int lo = 1;
        int hi = (int)1e9;
        int ans = hi;
        int n = weights.size();

        auto check = [&](int ability) -> bool {
            int i = 0;
            int days_needed = 0;
            while (i < n) {
                int curr_weight = 0;
                if (weights[i] > ability) {
                    return false;
                }

                while (i < n && curr_weight + weights[i] <= ability) {
                    curr_weight += weights[i];
                    i++;
                }
                days_needed++;
            }

            return days_needed <= days;
            };


        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (check(mid)) {
                ans = mid;
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        return ans;
    }
};