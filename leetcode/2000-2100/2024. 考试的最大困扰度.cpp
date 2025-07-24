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
    int maxConsecutiveAnswers(string answerKey, int k) {
        int n = answerKey.size();
        int left = 0;
        int cnt = 0;
        int ans = 0;
        for (int right = 0; right < n; right++) {
            if (answerKey[right] == 'F') {
                cnt++;
            }
            while (cnt > k) {
                if (answerKey[left] == 'F') {
                    cnt--;
                }
                left++;
            }
            ans = max(ans, right - left + 1);
        }

        left = 0;
        cnt = 0;
        for (int right = 0; right < n; right++) {
            if (answerKey[right] == 'T') {
                cnt++;
            }
            while (cnt > k) {
                if (answerKey[left] == 'T') {
                    cnt--;
                }
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};