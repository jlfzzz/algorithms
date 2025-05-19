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
    int numberOfArrays(vector<int> &differences, int lower, int upper) {
        long long prefix = 0, mn = 0, mx = 0;
        for (long long d : differences) {
            prefix += d;
            mn = min(mn, prefix);
            mx = max(mx, prefix);
        }

        return max(upper - mx - lower + mn + 1, 0LL);

    }
};