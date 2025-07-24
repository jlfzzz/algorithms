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
    int hIndex(vector<int> &citations) {
        int left = 0;
        int n = citations.size();
        int right = citations.size();

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (n - mid > citations[mid]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return n - left;
    }
};