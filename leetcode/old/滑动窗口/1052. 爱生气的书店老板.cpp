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
#include <cstring>

using namespace std;

class Solution {
public:
    int maxSatisfied(vector<int> &customers, vector<int> &grumpy, int minutes) {
        int n = customers.size();
        int total = 0;
        for (int i = minutes; i < n; i++) {
            total += !grumpy[i] ? customers[i] : 0;
        }

        int left = 0;
        int window = 0;
        int right = 0;
        for (; right < minutes;right++) {
            window += customers[right];
        }
        int ans = window + total;

        for (; right < n; right++) {
            window += customers[right];
            window -= customers[left];
            total -= !grumpy[right] ? customers[right] : 0;
            total += !grumpy[left] ? customers[left] : 0;
            ans = max(ans, total + window);
            left++;
        }
        return ans;
    }
};