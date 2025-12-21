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
    int minDeletionSize(vector<string> &strs) {
        int n = SZ(strs);
        int m = SZ(strs[0]);

        vi bad(n - 1, 0);
        int ans = 0;

        F(j, 0, m - 1) {
            bool flag = false;

            F(i, 0, n - 2) {
                if (!bad[i] && strs[i][j] > strs[i + 1][j]) {
                    flag = true;
                    break;
                }
            }

            if (flag) {
                ans++;
            } else {
                F(i, 0, n - 2) {
                    if (!bad[i] && strs[i][j] < strs[i + 1][j]) {
                        bad[i] = 1;
                    }
                }
            }
        }
        return ans;
    }
};
