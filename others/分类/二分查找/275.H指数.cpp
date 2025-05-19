#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    int hIndex(vector<int> &citations) {
        int n = citations.size();

        // 二分查找H-Index
        int left = 0, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            // 检查是否有n-mid篇论文至少被引用了citations[mid]次
            if (citations[mid] >= n - mid) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return n - left;
    }
};