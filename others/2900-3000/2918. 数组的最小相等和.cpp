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

using namespace std;

class Solution {
public:
    long long minSum(vector<int> &nums1, vector<int> &nums2) {
        long long sum1 = 0;
        int zero1 = 0;
        long long sum2 = 0;
        int zero2 = 0;
        long long ans = 0;

        for (int x : nums1) {
            sum1 += x;
            if (x == 0) {
                zero1++;
            }
        }

        for (int x : nums2) {
            sum2 += x;
            if (x == 0) {
                zero2++;
            }
        }

        sum1 += zero1;
        sum2 += zero2;

        if (sum1 > sum2) {
            if (zero2 == 0) {
                return -1;
            }
            ans = sum1;
        } else if (sum1 < sum2) {
            if (zero1 == 0) {
                return -1;
            }
            ans = sum2;
        } else {
            ans = sum1;
        }

        return ans;
    }
};