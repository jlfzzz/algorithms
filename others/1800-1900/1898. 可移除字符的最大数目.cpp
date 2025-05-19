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
    int maximumRemovals(string s, string p, vector<int> &removable) {
        int n = s.size();
        int m = p.size();
        int lo = 0;
        int hi = removable.size() + 1;
        int ans = -1;

        auto check = [&](int mid, string &new_s) -> bool {
            int j = 0;
            for (char c : new_s) {
                if (c == p[j]) {
                    j++;
                }
            }
            return j == m;
            };

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            string new_s = s;
            for (int i = 0; i < mid; i++) {
                new_s[removable[i]] = '#';
            }
            if (check(mid, new_s)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return ans;
    }
};