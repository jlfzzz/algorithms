#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int> &piles, int h) {
        int upper = ranges::max(piles) + 1;
        int lower = 1;

        auto check = [&](int speed) -> bool {
            int sum = 0;
            for (int i : piles) {
                sum += (i + speed - 1) / speed;
            }
            return sum <= h;
            };

        while (lower < upper) {
            int mid = lower + (upper - lower) / 2;
            if (check(mid)) {
                upper = mid;
            } else {
                lower = mid + 1;
            }
        }
        return lower;
        
    }
};