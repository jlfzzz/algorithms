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

class RangeFreqQuery {
public:
    unordered_map<int, vector<int>> map;
    RangeFreqQuery(vector<int> &arr) {
        for (int i = 0; i < arr.size(); i++) {
            map[arr[i]].emplace_back(i);
        }
    }

    int query(int left, int right, int value) {
        auto it = map.find(value);
        if (it == map.end()) return 0;

        auto start = lower_bound(it->second.begin(), it->second.end(), left);
        auto end = upper_bound(it->second.begin(), it->second.end(), right);
        return end - start;
    }
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */