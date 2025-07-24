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
        int lengthAfterTransformations(string s, int t) {
            int n = s.size();
            vector<int> record(26);
            int MOD = 1e9 + 7;
    
            for (char c : s) {
                record[c - 'a']++;
            }
    
            int added = 0;
            vector<int> dp(t + 1);
            //dp[0] = n;
            for (int i = 1; i <= t; i++) {
                vector<int> temp(26);
                for (int j = 2; j < 26; j++) {
                    temp[j] = record[j - 1];
                }
                temp[0] = record[25];
                temp[1] = (record[0] + record[25]) % MOD;
                swap(temp, record);
            }
    
            int ans = 0;
            for (int x :record) {
                ans = (ans + x) % MOD;
            }
            return ans;
        }
    };