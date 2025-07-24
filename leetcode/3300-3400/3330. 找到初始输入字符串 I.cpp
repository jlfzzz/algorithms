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

using namespace std;

class Solution {
public:
    int possibleStringCount(string word) {
        int n = word.size();
        int i = 1;
        int count = 1;
        int ans = 1;
        while (i < n) {
            if (word[i] != word[i - 1]) {
                ans += count - 1;
                count = 1;
            } else {
                count++;
                if (i == n - 1) {
                    ans += count - 1;
                }
            }
            i++;
        }
        return ans;
    }
};