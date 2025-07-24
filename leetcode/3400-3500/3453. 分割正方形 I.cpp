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

using namespace std;

class Solution {
public:
    double separateSquares(vector<vector<int>> &squares) {
        long long tot_area = 0;
        int max_y = 0;
        for (auto &sq : squares) {
            int l = sq[2];
            tot_area += 1LL * l * l;
            max_y = max(max_y, sq[1] + l);
        }

        auto check = [&](double y) -> bool {
            double area = 0;
            for (auto &sq : squares) {
                double yi = sq[1];
                if (yi < y) {
                    double l = sq[2];
                    area += l * min(y - yi, l);
                }
            }
            return area >= tot_area / 2.0;
            };

        double left = 0, right = max_y;
        for (int i = 0; i < 47; i++) {
            double mid = (left + right) / 2;
            (check(mid) ? right : left) = mid;
        }
        return (left + right) / 2; // 区间中点误差小
    }
};

class Solution {
public:
    double separateSquares(vector<vector<int>> &squares) {
        long long tot_area = 0;
        int max_y = 0;
        for (auto &sq : squares) {
            int l = sq[2];
            tot_area += 1LL * l * l;
            max_y = max(max_y, sq[1] + l);
        }

        const int M = 100'000;
        auto check = [&](long long multi_y) -> bool {
            long long area = 0;
            for (auto &sq : squares) {
                long long y = sq[1];
                if (y * M < multi_y) {
                    long long l = sq[2];
                    area += l * min(multi_y - y * M, l * M);
                }
            }
            return area * 2 >= tot_area * M;
            };

        long long left = 0, right = 1LL * max_y * M;
        while (left + 1 < right) {
            long long mid = left + (right - left) / 2;
            (check(mid) ? right : left) = mid;
        }
        return 1.0 * right / M;
    }
};