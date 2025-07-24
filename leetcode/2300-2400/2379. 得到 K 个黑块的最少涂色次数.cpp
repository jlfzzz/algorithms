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

using namespace std;

class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int n = blocks.size();
        int left = 0;
        int blackCount = 0;
        int whiteCount = 0;
        int ans = 999;
        for (int right = 0; right < n; right++) {
            if (blocks[right] == 'W') {
                whiteCount++;
            }
            blackCount++;
            if (blackCount == k) {
                ans = min(ans, whiteCount);
                while (left < right && blocks[left] != 'W') {
                    left++;
                    blackCount--;
                }

                left++;
                blackCount--;
                if (whiteCount > 0)
                    whiteCount--;
            }
        }
        return ans;
    }
};