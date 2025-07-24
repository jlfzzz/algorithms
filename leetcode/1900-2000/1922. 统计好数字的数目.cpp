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
    int countGoodNumbers(long long n) {
        long long odd = n / 2;
        long long even = n / 2 + n % 2;

        auto pow = [&](this auto &&pow, int x, long long n) -> long long {
            if (n == 0) return 1;

            long long i = pow(x, n / 2);
            i = i * (i % 1000000007);
            return n % 2 == 1 ? (i * x) % 1000000007 : i % 1000000007;
            };
        return (pow(5, even) * pow(4, odd)) % 1000000007;
    }
};