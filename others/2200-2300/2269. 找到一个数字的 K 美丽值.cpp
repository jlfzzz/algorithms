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
    int divisorSubstrings(int num, int k) {
        string s = to_string(num);
        int ans = 0;
        for (int i = k; i <= s.size(); i++) {
            int x = stoi(s.substr(i - k, k)); // 长为 k 的子串
            if (x > 0 && num % x == 0) { // 子串能整除 num
                ans++;
            }
        }
        return ans;
    }
};