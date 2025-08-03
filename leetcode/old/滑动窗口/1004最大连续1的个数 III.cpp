#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include <set>
#include <unordered_map>


using namespace std;

class Solution {
public:
    int longestOnes(vector<int> &nums, int k) {
        int ans = 0;
        int left = 0;
        int zeroCount = 0;

        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) {
                zeroCount++;
            }

            while (zeroCount > k) {
                if (nums[left] == 0) {
                    zeroCount--;
                }
                left++;

            }

            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};