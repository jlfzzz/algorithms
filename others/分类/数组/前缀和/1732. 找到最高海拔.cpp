#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int largestAltitude(vector<int> &gain) {
        int curr = 0;
        int ans = 0;
        for (int diff : gain) {
            curr += diff;
            ans = max(ans, curr);
        }
        return ans;
    }
};