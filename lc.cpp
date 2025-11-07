#include <bits/stdc++.h>
using namespace std;

constexpr int N = int(1e5 + 5);

int INIT = [] { return 0; }();

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);
using ll = long long;

class Solution {
public:
    long long maxPower(vector<int> &stations, int r, int k) {
        int n = stations.size();

        ll lo = 0;
        ll hi = accumulate(stations.begin(), stations.end(), 0ll) + k;
        ll ans = 0;

        auto check = [&](ll target) -> bool {
            ll window = 0;
            int right = 0;
            vector<ll> diff(n + 1, 0);
            ll used = 0;

            for (int i = 0; i < n; i++) {
                window += diff[i];
                while (right < n && right - i <= r) {
                    window += stations[right];
                    right++;
                }
                if (i - r - 1 >= 0) {
                    window -= stations[i - r - 1];
                }

                if (window < target) {
                    ll need = target - window;
                    used += need;
                    if (used > k) {
                        return false;
                    }

                    window += need;
                    int end = min(n - 1, i + 2 * r);
                    diff[end + 1] -= need;
                }
            }
            return true;
        };

        while (lo <= hi) {
            ll mid = lo + (hi - lo) / 2;
            if (check(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return ans;
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // Solution sol1;
    // ll n = 11;
    // vector<int> nums1{}, nums{};
}
