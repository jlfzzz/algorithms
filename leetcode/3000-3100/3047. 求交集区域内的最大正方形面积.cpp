#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multiset =
    tree<pair<long long, long long>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int N = int(5e5 + 5);
int INIT = [] { return 0; }();

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
    long long largestSquareArea(vector<vector<int>> &bottomLeft, vector<vector<int>> &topRight) {
        int n = SZ(bottomLeft);
        ll ans = 0;

        F(i, 0, n - 1) {
            int l1 = bottomLeft[i][0];
            int b1 = bottomLeft[i][1];
            int r1 = topRight[i][0];
            int t1 = topRight[i][1];

            F(j, i + 1, n - 1) {
                int l2 = bottomLeft[j][0];
                int b2 = bottomLeft[j][1];
                int r2 = topRight[j][0];
                int t2 = topRight[j][1];

                int L = max(l1, l2);
                int R = min(r1, r2);

                int B = max(b1, b2);
                int T = min(t1, t2);

                if (L < R && B < T) {
                    ll width = R - L;
                    ll height = T - B;

                    ll side = min(width, height);
                    ans = max(ans, side * side);
                }
            }
        }
        return ans;
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
