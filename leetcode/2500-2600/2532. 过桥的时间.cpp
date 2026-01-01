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
    int findCrossingTime(int n, int k, vector<vector<int>> &time) {
        prq<pii> waitL, waitR;
        prq<pii, vp, greater<>> workL, workR;

        F(i, 0, k - 1) { waitL.push({time[i][0] + time[i][2], i}); }

        ll cur = 0;
        while (n > 0 || !workR.empty() || !waitR.empty()) {
            while (!workL.empty() && workL.top().fi <= cur) {
                auto [t, idx] = workL.top();
                workL.pop();
                waitL.push({time[idx][0] + time[idx][2], idx});
            }
            while (!workR.empty() && workR.top().fi <= cur) {
                auto [t, idx] = workR.top();
                workR.pop();
                waitR.push({(ll) time[idx][0] + time[idx][2], idx});
            }

            if (!waitR.empty()) {
                auto [t, idx] = waitR.top();
                waitR.pop();
                cur += time[idx][2];

                workL.push({cur + time[idx][3], idx});
            } else if (!waitL.empty() && n > 0) {
                auto [t, idx] = waitL.top();
                waitL.pop();
                cur += time[idx][0];
                n--;
                workR.push({cur + time[idx][1], idx});
            } else {
                ll nxt = INF;
                if (!workL.empty())
                    nxt = min(nxt, workL.top().fi);
                if (!workR.empty())
                    nxt = min(nxt, workR.top().fi);
                cur = nxt;
            }
        }
        return cur;
    }
};
