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
    int minimumPairRemoval(vector<int> &nums) {
        int n = SZ(nums);
        vl a(n);

        F(i, 0, n - 1) { a[i] = nums[i]; }

        vi L(n), R(n);
        vector<bool> removed(n, false);

        F(i, 0, n - 1) {
            L[i] = i - 1;
            R[i] = i + 1;
        }
        R[n - 1] = -1;

        int bad = 0;
        prq<pii, vp, greater<pii>> pq;

        F(i, 0, n - 2) {
            if (a[i] > a[i + 1]) {
                bad++;
            }
            pq.push({a[i] + a[i + 1], i});
        }

        int cnt = 0;

        while (!pq.empty() && bad > 0) {
            auto [s, i] = pq.top();
            pq.pop();

            int j = R[i];

            if (removed[i] || j == -1 || removed[j])
                continue;

            if (s != a[i] + a[j])
                continue;

            cnt++;

            int l = L[i];
            if (l != -1) {
                if (a[l] > a[i])
                    bad--;
            }
            if (a[i] > a[j])
                bad--;

            int r = R[j];
            if (r != -1) {
                if (a[j] > a[r])
                    bad--;
            }

            a[i] += a[j];
            removed[j] = true;

            R[i] = r;
            if (r != -1)
                L[r] = i;

            if (l != -1) {
                if (a[l] > a[i])
                    bad++;
            }
            if (r != -1) {
                if (a[i] > a[r])
                    bad++;
            }

            if (r != -1) {
                pq.push({a[i] + a[r], i});
            }
            if (l != -1) {
                pq.push({a[l] + a[i], l});
            }
        }
        return cnt;
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
