#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <ranges>

using namespace std;

class Solution {
public:
    long long countSubarrays(vector<int> &nums, long long k) {
        long long ans = 0;
        int left = 0;
        long long sum = 0;

        for (int right = 0; right < nums.size(); ++right) {
            sum += nums[right];
            long long point = sum * (right - left + 1);

            while (point >= k) {
                sum -= nums[left];
                left++;
                point = sum * (right - left + 1);
            }

            ans += right - left + 1;
        }

        return ans;
    }
};