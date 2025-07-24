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

using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            vector<int> visited(n, 0);
            // visited[0] = true;
            int j = i;
            int dir = nums[j] > 0;
            int flag = true;
            while (1) {
                if (!visited[j]) {
                    if (nums[j] > 0 != dir) {
                        flag = false;
                        break;
                    }
                    visited[j] = true;
                    j = (j + nums[j] + 10000 * n) % n;
                } else {
                    break;
                }
            }
            
            if (!flag) {
                continue;
            }

            int k = j;
            k = (k + nums[k] + 10000 * n) % n;
            int count = 1;
            while (k != j) {
                k = (k + nums[k] + 10000 * n) % n;
                count++;
            }
            if (count > 1) {
                return true;
            }
        }

        return false;
    }
};