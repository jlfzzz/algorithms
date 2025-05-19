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
    string dynamicPassword(string password, int target) {
        int n = password.size();
        for (int i = 0; i < target; i++) {
            password += password[i];
        }
        return password.substr(target, n);
    }
};