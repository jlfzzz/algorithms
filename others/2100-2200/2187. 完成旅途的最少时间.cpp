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

// long long 是你爹？

class Solution {
public:
    long long minimumTime(vector<int> &time, int totalTrips) {
        int n = time.size();
        long long mn = *min_element(time.begin(), time.end());
        long long hi = mn * totalTrips + 1;
        long long lo = 1;
        long long ans = hi;

        auto check = [&](long long mid) -> bool {
            long long total = 0;
            for (int x : time) {
                total += mid / x;
            }

            return total >= totalTrips;
            };

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;

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