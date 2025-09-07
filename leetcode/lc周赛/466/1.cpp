#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;

class Solution {
public:
    int countBinaryPalindromes(long long n) {
        if (n == 0) {
            return 1;
        }


        int m = bit_width((ull) n);

        vector<vector<vector<int>>> memo(100, vector<vector<int>>(2, vector<int>(2, -1)));
        auto dfs = [&](this auto &&dfs, int i, bool is_num, bool is_hi) -> int {
            if (i == (m + 1) / 2) {
                return 1;
            }

            if (memo[i][is_num][is_hi] != -1) {
                return memo[i][is_num][is_hi];
            }

            int lo = is_num ? 1 : 0;
            int hi = is_hi ? (n >> (m - i - 1) & 1) : 1;

            int res = 0;
            for (int j = lo; j <= hi; j++) {
                res += dfs(i + 1, true, is_hi && (j == (n >> (m - i - 1) & 1)));
            }

            memo[i][is_num][is_hi] = res;
            return res;
        };

        return dfs(0, 0, 1);
    }
};






class Solution {
public:
    long long bowlSubarrays(vector<int> &nums) {
        int n = nums.size();
        vector<int> left(n, 1), right(n, 1);
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[i - 1])
                left[i] = left[i - 1] + 1;
        }
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1])
                right[i] = right[i + 1] + 1;
        }

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans += 1ll * (left[i] - 1) * (right[i] - 1);
        }
        return ans;
    }
};






class Solution {
public:
    int minOperations(string s) {
        vector<int> cnt(26);

        for (char c: s) {
            cnt[c - 'a']++;
        }


        int pos = -1;
        for (int i = 1; i < 26; i++) {
            if (cnt[i]) {
                pos = i;
                break;
            }
        }

        if (pos == -1) {
            return 0;
        }

        return 26 - pos;
    }
};

class Solution {
public:
    int minOperations(vector<int> &nums) {
        int n = nums.size();
        bool f = true;
        int a = nums[0];
        for (int i = 1; i < n; i++) {
            if (nums[i] != a) {
                f = false;
            }
        }

        if (f) {
            return 0;
        }
        return 1;
    }
};
