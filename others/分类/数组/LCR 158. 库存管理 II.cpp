#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

class Solution {
public:
    int inventoryManagement(vector<int> &stock) {
        int comp = stock.size() / 2;
        unordered_map<int, int> map;
        int ans = 0;
        for (int i : stock) {
            map[i]++;
            if (map[i] > comp) return i;
        }
        return ans;
    }
};