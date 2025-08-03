#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

// 方法二 采用分组，不用排序 0(n)

class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int> &asteroids) {
        ranges::sort(asteroids);
        long long sum = mass;
        for (int i : asteroids) {
            if (sum >= i) {
                sum += i;
            } else {
                return false;
            }
        }
        return true;
    }
};

class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int> &asteroids) {
        vector<int> min(17, -1);
        vector<long long> sum(17);
        for (int i = 0; i < asteroids.size(); i += 1) {
            int h = 31 - __builtin_clz(asteroids[i]);
            if (min[h] == -1 or asteroids[i] < min[h]) min[h] = asteroids[i];
            sum[h] += asteroids[i];
        }
        long long cur = mass;
        for (int i = 0; i < 17; i += 1) {
            if (cur < min[i]) return false;
            cur += sum[i];
        }
        return true;
    }
};
