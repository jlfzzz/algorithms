#include <algorithm>
#include <ranges>
#include <vector>

using namespace std;

class Solution {
public:
    bool check(vector<int> &price, int diff, int select) {
        int n = price.size();
        int selected = 1;
        int last = price[0];

        for (int i = 1; i < n; i++) {
            while (i < n && price[i] - last < diff) {
                i++;
            }
            if (i == n) {
                break;
            }
            selected++;
            last = price[i];
        }
        return selected >= select;
    }

    int maximumTastiness(vector<int> &price, int k) {
        int right = *ranges::max_element(price);
        int left = 0;
        int ans = 0;
        ranges::sort(price);

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (check(price, mid, k)) {
                left = mid + 1;
                ans = mid;
            } else {
                right = mid;
            }
        }
        return ans;
    }
};

