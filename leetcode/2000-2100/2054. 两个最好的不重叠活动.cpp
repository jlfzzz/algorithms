#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)


class Solution {
public:
    int maxTwoEvents(vector<vector<int>> &events) {
        int n = SZ(events);
        sort(all(events));
        vi dp(n + 1, 0);

        int ans = 0;
        F(i, 0, n - 1) {
            auto &v = events[i];
            if (i > 0)
                dp[i] = max(dp[i], dp[i - 1]);
            ans = max(ans, v[2] + dp[i]);

            int l = i + 1, r = n - 1, nxt = n;
            while (l <= r) {
                int mid = l + (r - l) / 2;
                if (events[mid][0] > v[1]) {
                    nxt = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }

            if (nxt < n) {
                dp[nxt] = max(dp[nxt], v[2]);
            }
        }

        return ans;
    }
};
