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
    long long minMergeCost(vector<vector<int>> &lists) {
        int n = SZ(lists);
        int u = 1 << n;

        vl dp(u, INF);
        vl med(u), len(u);

        F(mask, 1, u - 1) {
            vi temp;

            int lens = 0;
            F(i, 0, n - 1) {
                if ((mask >> i) & 1) {
                    temp.ins(temp.end(), all(lists[i]));
                    lens += SZ(lists[i]);
                }
            }

            ranges::sort(temp);
            med[mask] = temp[(lens - 1) / 2];
            len[mask] = lens;

            if (popcount((unsigned) mask) == 1) {
                dp[mask] = 0;
            }
        }

        F(mask, 1, u - 1) {
            if (dp[mask] == 0)
                continue;

            for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) {
                int other = mask ^ sub;

                if (other > sub) {
                    break;
                }

                if (dp[sub] != INF && dp[other] != INF) {
                    ll c = len[mask] + abs(med[sub] - med[other]);
                    dp[mask] = min(dp[mask], dp[sub] + dp[other] + c);
                }
            }
        }

        return dp[u - 1];
    }
};
