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
    int maximizeSquareArea(int m, int n, vector<int> &hFences, vector<int> &vFences) {
        hFences.push_back(1);
        hFences.push_back(m);
        vFences.push_back(1);
        vFences.push_back(n);
        ranges::sort(hFences);
        ranges::sort(vFences);

        int sz1 = SZ(hFences);
        unordered_map<int, int> cnt1, cnt2;
        F(i, 0, sz1 - 1) {
            F(j, i + 1, sz1 - 1) { cnt1[hFences[j] - hFences[i]]++; }
        }

        int sz2 = SZ(vFences);
        F(i, 0, sz2 - 1) {
            F(j, i + 1, sz2 - 1) { cnt2[vFences[j] - vFences[i]]++; }
        }

        ll ans = -1;
        for (auto [x, c]: cnt1) {
            if (cnt2.contains(x)) {
                ans = max(ans, 1ll * x * x);
            }
        }

        return ans % MOD;
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
