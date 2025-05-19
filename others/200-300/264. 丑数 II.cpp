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
#include <set>
#include <queue>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        int nums[] = { 2, 3, 5 };
        set<long> s;
        priority_queue<long, vector<long>, greater<long>> q;
        s.insert(1);
        q.push(1);
        for (int i = 1; i <= n; i++) {
            long x = q.top();
            q.pop();
            if (i == n)
                return (int)x;
            for (int num = 0; num < 3; num++) {
                long t = nums[num] * x;
                if (!s.count(t)) {
                    s.insert(t);
                    q.push(t);
                }
            }
        }
        return -1;
    }
};