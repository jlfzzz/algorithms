#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <numeric>

using namespace std;

class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) {
        if (s.length() <= 2) {
            return s.length();
        }

        int ans = 0;
        int left = 0;
        char last = s[0];
        int lastSeen = -1;

        for (int right = 1; right < s.length(); right++) {
            char current = s[right];
            if (current == last) {
                if (lastSeen == -1) {
                    lastSeen = right;
                } else {
                    left = lastSeen;
                    lastSeen = right;
                }
            }

            ans = max(ans, right - left + 1);

            last = current;
        }
    }
};