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

using namespace std;

class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>> &dominoes) {
        int cnt[10][10] = {};
        int ans = 0;
        for (auto d : dominoes) {
            int a = min(d[0], d[1]);
            int b = max(d[0], d[1]);
            ans += cnt[a][b];
            cnt[a][b]++;
        }
        return ans;
    }
};

class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>> &dominoes) {
        unordered_map<string, int> mp;
        for (auto &v : dominoes) {
            string s1 = to_string(v[0]) + to_string(v[1]);
            string s2 = to_string(v[1]) + to_string(v[0]);
            if (!mp[s1] && !mp[s2]) {
                mp[s1]++;
            } else {
                if (mp[s1]) {
                    mp[s1]++;
                } else {
                    mp[s2]++;
                }
            }
        }

        int ans = 0;
        for (auto &p : mp) {
            if (p.second >= 2) {
                ans += (p.second * (p.second - 1)) / 2;
            }
        }
        return ans;
    }
};