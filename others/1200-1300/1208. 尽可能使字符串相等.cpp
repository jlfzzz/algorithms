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
#include <set>
#include <random>

using namespace std;

class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int n = s.length();
        vector<int> diff(n, 0);
        for (int i = 0; i < n; i++) {
            diff[i] = abs(s[i] - t[i]);
        }
        int maxLength = 0;
        int start = 0, end = 0;
        int sum = 0;
        while (end < n) {
            sum += diff[end];
            while (sum > maxCost) {
                sum -= diff[start];
                start++;
            }
            maxLength = max(maxLength, end - start + 1);
            end++;
        }
        return maxLength;
    }
};