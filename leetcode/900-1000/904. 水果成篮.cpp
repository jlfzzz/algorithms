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
    int totalFruit(vector<int> &fruits) {
        int n = fruits.size();
        int left = 0;
        unordered_map<int, int> window;
        int ans = 0;

        for (int right = 0; right < n; right++) {
            int x = fruits[right];
            window[x]++;
            while (window.size() > 2) {
                window[fruits[left]]--;
                if (window[fruits[left]] == 0) {
                    window.erase(fruits[left]);
                }
                left++;
            }

            int temp = 0;
            for (auto &p : window) {
                temp += p.second;
            }
            ans = max(ans, temp);
        }
        return ans;
    }
};