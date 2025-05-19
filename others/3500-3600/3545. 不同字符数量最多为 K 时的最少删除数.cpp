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
        int minDeletion(string s, int k) {
            vector<int> record(26, 0);
            for (char c : s) {
                record[c - 'a']++;
            }
    
            int count = 0;
            for (int x : record) {
                if (x > 0) {
                    count++;
                }
            }
            if (count <= k) {
                return 0;
            }
            
            sort(record.begin(), record.end());
            int i = 0;
            while (record[i] == 0) {
                i++;
            }
    
            int ans = 0;
            while (count > k) {
                ans += record[i];
                count--;
                i++;
            }
    
            return ans;
        }
    };