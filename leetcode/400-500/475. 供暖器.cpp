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

// 没必要强行二分，直接双指针

class Solution {
public:
    int findRadius(vector<int> &houses, vector<int> &heaters) {
        int n = houses.size();
        int hi = INT_MAX;
        int lo = 0;
        int ans = hi;
        int heaters_size = heaters.size();

        ranges::sort(houses);
        ranges::sort(heaters);

        auto check = [&](int mid) -> bool {
            int i = 0;
            int j = 0;
            while (j < n) {
                if (i == heaters_size) {
                    return false;
                }

                if (houses[j] < heaters[i] - mid || houses[j] > heaters[i] + mid) {
                    i++;
                } else {
                    j++;
                }
            }

            return j == n;

            };

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (check(mid)) {
                ans = min(ans, mid);
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        return ans;
    }
};