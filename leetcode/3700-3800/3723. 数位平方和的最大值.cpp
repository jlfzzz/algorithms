#include <bits/stdc++.h>
using namespace std;

constexpr int N = int(1e5 + 5);

int INIT = [] { return 0; }();

using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);
using ll = long long;

class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        string s(num, '0');
        for (int i = 0; i < num; i++) {
            if (sum > 9) {
                s[i] = '9';
                sum -= 9;
            } else {
                s[i] = '0' + sum;
                break;
            }
        }

        if (sum) {
            s = "";
        }
        return s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution sol1;
    ll n = 11;
    vector<int> nums1{}, nums{};
}
