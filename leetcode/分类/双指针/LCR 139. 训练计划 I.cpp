#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> trainingPlan(vector<int> &actions) {
        int n = actions.size();
        int left = 0;
        int right = n - 1;

        while (left < right) {
            int curr = actions[left];
            if (curr % 2 == 0) {
                while (left < right && actions[right] % 2 == 0) {
                    right--;
                }

                actions[left] = actions[right];
                actions[right] = curr;
                right--;
            }
            left++;
        }
        return actions;
    }
};