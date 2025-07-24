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

using namespace std;

class Solution {
public:
    int kConcatenationMaxSum(vector<int> &arr, int k) {
        int n = arr.size();
        int mod = 1000000007;

        long long maxParts = 0;
        long long parts = 0;
        long long sum = 0;
        for (int i = 0; i < min(2, k) * n; i++) {
            if (i < n) sum += arr[i];
            parts = max({ parts + (long long)arr[i % n], (long long)arr[i % n], 0LL });
            maxParts = max(maxParts, parts);
        }

        if (sum > 0 && k > 2) {
            long long r = (sum * (k - 2)) % mod;
            maxParts += r;
        }

        return (int)maxParts % mod;

    }
};