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
    vector<int> recoverOrder(vector<int> &order, vector<int> &friends) {
        unordered_map<int, int> cnt;
        int n = order.size();
        for (int i = 0; i < n; i++) {
            cnt[order[i]] = i;
        }

        vector<pii> ans;
        for (int x: friends) {
            int pos = cnt[x];
            ans.emplace_back(pos, x);
        }

        ranges::sort(ans);
        vector<int> ans2;
        for (auto [a, b]: ans) {
            ans2.push_back(b);
        }
        return ans2;
    }
};
