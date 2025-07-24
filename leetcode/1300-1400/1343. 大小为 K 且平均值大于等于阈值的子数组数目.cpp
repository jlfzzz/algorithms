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
    int numOfSubarrays(vector<int> &arr, int k, int threshold) {
        int ans = 0;
        int sum = 0;
        int left = 0;
        int n = arr.size();
        for (int right = 0; right < n; right++) {
            sum += arr[right];

            if (right - left + 1 == k) {
                if (sum / k >= threshold) ans++;
                sum -= arr[left];
                left++;
            }
        }
        return ans;
    }
};