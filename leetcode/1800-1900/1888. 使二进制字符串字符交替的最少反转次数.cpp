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

using namespace std;

class Solution {
public:
    int minFlips(string s) {
        int n = s.size();
        int count = 0;
        int ans = n;

        for (int right = 0; right < 2 * n; right++) {
            int curr = s[right % n] - '0';

            if (right % 2 != curr % 2) {
                count++;
            }

            int left = right - n + 1;
            if (left >= 0) {
                ans = min({ ans, count, n - count });
                if ((s[left % n] - '0') % 2 != left % 2) {
                    count--;
                }
            }
        }

        return ans;
    }
};