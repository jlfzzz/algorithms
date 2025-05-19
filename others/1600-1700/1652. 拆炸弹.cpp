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
#include <cstring>

using namespace std;

class Solution {
public:
    vector<int> decrypt(vector<int> &code, int k) {
        int n = code.size();
        if (k == 0) return vector<int>(n, 0);

        vector<int> result(n);
        int window = 0;

        if (k > 0) {
            // 初始窗口：第一个元素后面的k个元素
            for (int i = 1; i <= k; i++) {
                window += code[i % n];
            }
            result[0] = window;

            // 滑动窗口
            for (int i = 1; i < n; i++) {
                window -= code[i % n];
                window += code[(i + k) % n];
                result[i] = window;
            }
        } else {
            // k为负数的情况
            k = -k; // 将k转为正数便于计算

            // 初始窗口：第一个元素前面的k个元素
            for (int i = 1; i <= k; i++) {
                window += code[(n - i) % n];
            }
            result[0] = window;

            // 滑动窗口
            for (int i = 1; i < n; i++) {
                window -= code[(n - k + i - 1) % n];
                window += code[(i - 1) % n];
                result[i] = window;
            }
        }

        return result;
    }
};