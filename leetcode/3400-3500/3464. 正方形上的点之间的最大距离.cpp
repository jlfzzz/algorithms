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
    int maxDistance(int side, vector<vector<int>> &points, int k) {
        vector<int> dis;

        for (auto &v: points) {
            int x = v[0], y = v[1];

            if (x == 0) {
                dis.push_back(y);
            } else if (y == side) {
                dis.push_back(x + side);
            } else if (x == side) {
                dis.push_back(side - y + 2 * side);
            } else {
                dis.push_back(3 * side + side - x);
            }
        }

        ranges::sort(dis);
        vector<int> arr = dis;

        for (int x: dis)
            arr.push_back(x + 4 * side);

        int n = arr.size();
        int half = n / 2;
        int ans = 1;
        int lo = 1, hi = 1e9 + 5;

        while (lo < hi) {
            int m = (lo + hi) / 2;

            auto check = [&](int target) -> bool {
                for (int start = 0; start < half; start++) {
                    int cnt = 1;
                    int last = arr[start];
                    for (int step = 1; step < k; step++) {
                        auto it = lower_bound(arr.begin() + start + 1, arr.begin() + start + half, last + target);
                        if (it == arr.begin() + start + half) {
                            cnt = -1;
                            break;
                        }
                        last = *it;
                        cnt++;
                    }
                    if (cnt > k)
                        return true;
                    if (cnt == k && 4 * side - (last - arr[start]) >= target) {
                        return true;
                    }
                }
                return false;
            };
            if (check(m)) {
                ans = m;
                lo = m + 1;
            } else {
                hi = m;
            }
        }

        return ans;
    }
};
