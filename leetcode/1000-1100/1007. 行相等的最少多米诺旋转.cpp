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
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        auto min_rot = [&](int target) -> int {
            int to_top = 0, to_bottom = 0;
            for (int i = 0; i < tops.size(); i++) {
                int x = tops[i], y = bottoms[i];
                if (x != target && y != target) {
                    return INT_MAX;
                }
                if (x != target) {
                    to_top++; // 把 y 旋转到上半
                } else if (y != target) {
                    to_bottom++; // 把 x 旋转到下半
                }
            }
            return min(to_top, to_bottom);
        };

        int ans = min(min_rot(tops[0]), min_rot(bottoms[0]));
        return ans == INT_MAX ? -1 : ans;
    }
};