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

class Solution {
public:
    string subStrHash(string s, int power, int mod, int k, int hashValue) {
        int n = s.length();
        // 用秦九韶算法计算 s[n-k:] 的哈希值，同时计算 pk=power^k
        long long hash = 0, pk = 1;
        for (int i = n - 1; i >= n - k; i--) {
            hash = (hash * power + (s[i] - 'a' + 1)) % mod;
            pk = pk * power % mod;
        }
        int ans = hash == hashValue ? n - k : 0;
        // 向左滑窗
        for (int i = n - k - 1; i >= 0; i--) {
            // 计算新的哈希值，注意 +mod 防止计算出负数
            hash = (hash * power + (s[i] - 'a' + 1) - pk * (s[i + k] - 'a' + 1) % mod + mod) % mod;
            if (hash == hashValue) {
                ans = i;
            }
        }
        return s.substr(ans, k);
    }
};