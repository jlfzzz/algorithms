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

using namespace std;

// 1 一次遍历，   2 两次遍历 + 向上取整

class Solution {
public:
    int numRabbits(vector<int> &answers) {
        unordered_map<int, int> mp;
        int ans = 0;

        int n = answers.size();
        for (int i = 0; i < n; i++) {
            int x = answers[i];
            if (x == 0) {
                ans += 1;
                continue;
            }

            if (mp.find(x) == mp.end()) {
                mp[x] = x;
                ans += x + 1;
            } else {
                mp[x]--;
                if (mp[x] == 0) {
                    mp.erase(x);
                }
            }
        }
        return ans;
    }
};

class Solution {
public:
    int numRabbits(vector<int> &answers) {
        unordered_map<int, int> cnt;
        for (int x : answers) {
            cnt[x]++;
        }
        int ans = 0;
        for (auto &[x, c] : cnt) {
            ans += (c + x) / (x + 1) * (x + 1);
        }
        return ans;
    }
};