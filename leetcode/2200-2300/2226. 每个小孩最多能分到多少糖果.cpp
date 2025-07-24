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
    int maximumCandies(vector<int> &candies, long long k) {
        long long total = accumulate(candies.begin(), candies.end(), 0LL);
        if (total < k) {
            return 0;
        }

        long long hi = total / k + 1;
        long long lo = 1;

        auto check = [&](long long q) -> bool {
            long long have = 0;
            for (int candy : candies) {
                if (candy < q) {
                    continue;
                } else {
                    have += candy / q;
                }

            }
            return have >= k;
            };

        long long ans = lo;
        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;

            if (check(mid)) {
                lo = mid + 1;
                ans = mid;
            } else {
                hi = mid;
            }
        }

        return ans;


    }
};