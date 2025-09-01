#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr long long inf = 0x3f3f3f3f / 2;



class Solution {
public:
    int minOperations(string s, int k) {
        int n = s.size();
        int cnt0 = count(s.begin(), s.end(), '0');

        vector<int> dis(n + 1, -1);
        deque<int> dq;
        dq.push_back(cnt0);
        dis[cnt0] = 0;
        set<int> even, odd;
        for (int i = 0; i <= n; i++) {
            if (i & 1) {
                odd.insert(i);
            } else {
                even.insert(i);
            }
        }
        if (cnt0 & 1)
            odd.erase(cnt0);
        else
            even.erase(cnt0);

        while (!dq.empty()) {
            int c0 = dq.front();
            dq.pop_front();

            int L1 = max(0, k - c0);
            int R1 = min(k, n - c0);

            if ((c0 + k) & 1) {
                auto it = odd.lower_bound(c0 + 2 * L1 - k);
                while (it != odd.end()) {
                    if (*it > c0 + 2 * R1 - k) {
                        break;
                    }
                    dis[*it] = dis[c0] + 1;
                    dq.push_back(*it);
                    odd.erase(it++);
                }
            } else {
                auto it = even.lower_bound(c0 + 2 * L1 - k);
                while (it != even.end()) {
                    if (*it > c0 + 2 * R1 - k) {
                        break;
                    }
                    dis[*it] = dis[c0] + 1;
                    dq.push_back(*it);
                    even.erase(it++);
                }
            }
        }
        return dis[0];
    }
};
