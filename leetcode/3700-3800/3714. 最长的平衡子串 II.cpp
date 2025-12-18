#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    int longestBalanced(string s) {
        int n = s.length();
        int ans = 0;

        for (char ch: {'a', 'b', 'c'}) {
            int len = 0;
            for (char c: s) {
                if (c == ch) {
                    len++;
                    ans = max(ans, len);
                } else {
                    len = 0;
                }
            }
        }

        auto calc = [&](char c1, char c2, char other) {
            unordered_map<int, int> mp;
            mp[0] = -1;
            int diff = 0;

            for (int i = 0; i < n; ++i) {
                if (s[i] == other) {
                    mp.clear();
                    mp[0] = i;
                    diff = 0;
                } else {
                    if (s[i] == c1)
                        diff++;
                    else if (s[i] == c2)
                        diff--;

                    if (mp.count(diff)) {
                        ans = max(ans, i - mp[diff]);
                    } else {
                        mp[diff] = i;
                    }
                }
            }
        };

        calc('a', 'b', 'c'); 
        calc('a', 'c', 'b'); 
        calc('b', 'c', 'a');

        map<pair<int, int>, int> mp3;
        mp3[{0, 0}] = -1;
        int ca = 0, cb = 0, cc = 0;

        for (int i = 0; i < n; ++i) {
            if (s[i] == 'a')
                ca++;
            else if (s[i] == 'b')
                cb++;
            else if (s[i] == 'c')
                cc++;

            int diff1 = ca - cb;
            int diff2 = cb - cc;

            if (mp3.count({diff1, diff2})) {
                ans = max(ans, i - mp3[{diff1, diff2}]);
            } else {
                mp3[{diff1, diff2}] = i;
            }
        }

        return ans;
    }
};
