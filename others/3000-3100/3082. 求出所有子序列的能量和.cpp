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
    int sumOfPower(vector<int> &nums, int k) {
        vector<long long> f(k + 1);
        f[0] = 1;
        for (int x : nums) {
            for (int j = k; j >= 0; j--) {
                f[j] = (f[j] * 2 + (j >= x ? f[j - x] : 0)) % 1'000'000'007;
            }
        }
        return f[k];
    }
};