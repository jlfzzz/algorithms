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

using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        auto pow = [&](this auto &&pow, double x, long long n) -> double {
            if (n == 0) return 1.0;

            double i = pow(x, n / 2);
            return n % 2 == 1 ? i * i * x : i * i;
            };
        long long N = n;
        return n >= 0 ? pow(x, n) : 1.0 / pow(x, -N);
    }
};