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
    int partition(vector<int> &nums, int left, int right) {
        int pivot = nums[right];
        int i = left;
        int j = right - 1;
        while (1) {
            while (i <= j && nums[i] < pivot) {
                i++;
            }
            while (i <= j && nums[j] > pivot) {
                j--;
            }
            if (i >= j) {
                break;
            }
            swap(nums[i], nums[j]);
            i++;
            j--;
        }
        swap(nums[right], nums[i]);
        return i;
    }

    int quick_sort(vector<int> &nums, int left, int right, int k) {
        int pi = partition(nums, left, right);

        if (nums.size() - pi == k) {
            return nums[pi];
        } else if (nums.size() - pi > k) {
            return quick_sort(nums, pi + 1, right, k);
        } else {
            return quick_sort(nums, left, pi - 1, k);
        }
    }

    int findKthLargest(vector<int> &nums, int k) {
        int n = nums.size();
        return quick_sort(nums, 0, n - 1, k);
    }
};