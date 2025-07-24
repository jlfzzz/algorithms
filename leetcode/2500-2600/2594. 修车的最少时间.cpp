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

using ll = long long;
class Solution {
public:
    long long repairCars(vector<int>& ranks, int cars) {
        ll hi = LONG_LONG_MAX;
        ll lo = 1;
        ll ans = hi;

        auto check = [&](ll time) -> bool {
            ll sum = 0;
            for (int rank : ranks) {
                sum += (ll)sqrt(time / rank);
                if (sum >= cars) {
                    return true;
                }
            }
            return false;
        };

        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;

            if (check(mid)) {
                hi = mid;
                ans = mid;
            } else {
                lo = mid + 1;
            }
        }

        return ans;
    }
};