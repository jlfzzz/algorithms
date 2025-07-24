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

using namespace std;

class Solution {
public:
    int maxScore(vector<int> &cardPoints, int k) {
        class Solution {
        public:
            int maxScore(vector<int> &cardPoints, int k) {
                int n = cardPoints.size();
                int total = 0;
                for (int x : cardPoints) total += x;
                int mn = total + 1;
                int sum = 0;
                int left = 0;
                for (int right = 0; right < n; right++) {
                    sum += cardPoints[right];
                    if (right - left + 1 == n - k) {
                        mn = min(mn, sum);
                        sum -= cardPoints[left];
                        left++;
                    }
                }
                return mn == total + 1 ? total : total - mn;
            }
        };
    }
};