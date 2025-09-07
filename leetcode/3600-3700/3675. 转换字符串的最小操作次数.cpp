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
