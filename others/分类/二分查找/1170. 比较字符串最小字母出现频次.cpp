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
    vector<int> numSmallerByFrequency(vector<string> &queries, vector<string> &words) {
        int m = words.size();
        vector<int> record;

        auto findFrequency = [&](string &s) -> int {
            char smallest = 'z';
            for (char c : s) {
                smallest = min(smallest, c);
            }
            return count(s.begin(), s.end(), smallest);
            };

        for (string &s : words) {
            record.emplace_back(findFrequency(s));
        }
        sort(record.begin(), record.end());

        vector<int> ans;
        for (string &s : queries) {
            int target = findFrequency(s);
            auto it = upper_bound(record.begin(), record.end(), target);
            ans.emplace_back(record.end() - it);
        }
        return ans;
    }
};