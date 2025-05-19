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
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int right = 1e8;
        int left = 1;
        int ans = right;

        auto check = [&](int speed) -> bool {
            if (speed == 0) return false; // Speed cannot be zero
            double total_time_taken = 0.0;
            int n = dist.size();

            for (int i = 0; i < n; ++i) {
                double time_for_segment = static_cast<double>(dist[i]) / speed; // Corrected: floating point division

                if (i < n - 1) { // For all segments except the last one
                    total_time_taken += std::ceil(time_for_segment);
                } else { // For the last segment
                    total_time_taken += time_for_segment;
                }
            }
            return total_time_taken <= hour;
        };

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (check(mid)) {
                ans = mid;
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return ans == 1e8 ? -1 : ans;
    }
};