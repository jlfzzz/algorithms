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
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int ans = 0;
        ranges::sort(arr2);
        for (int x : arr1) {
            if (ranges::lower_bound(arr2, x - d) == ranges::upper_bound(arr2, x + d)) ans++;
        }
        return ans;
    }
};