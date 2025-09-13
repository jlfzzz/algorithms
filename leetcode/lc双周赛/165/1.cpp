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
    vector<vector<int>> generateSchedule(int n) {
        if (n <= 4)
            return {};

        vector<vector<int>> ans;

        int cur = 2;
        for (int i = 1; i <= n; i += 2) {
            int x = 1;
            int y = cur;
            for (int j = 1; j <= n; j++) {
                vector<int> temp = {x, y};
                ans.emplace_back(temp);
                x = (x + 2) % n;
                if (x == 0) {
                    x = n;
                }

                y = (y + 2) % n;
                if (y == 0) {
                    y = n;
                }
            }

            x = 1, y = cur;
            for (int j = 1; j <= n; j++) {
                vector<int> temp = {y, x};
                ans.emplace_back(temp);
                x = (x + 2) % n;
                if (x == 0) {
                    x = n;
                }

                y = (y + 2) % n;
                if (y == 0) {
                    y = n;
                }
            }

            cur++;
        }

        if (n & 1) {
            int x = 1;
            int y = cur;
            for (int j = 1; j <= n; j++) {
                vector<int> temp = {x, y};
                ans.emplace_back(temp);
                x = (x + 2) % n;
                if (x == 0) {
                    x = n;
                }

                y = (y + 2) % n;
                if (y == 0) {
                    y = n;
                }
            }
        }

        vector<vector<int>> ans2;
        for (auto &v: ans) {
            ans2.emplace_back(vector<int>{v[0] - 1, v[1] - 1});
        }

        return ans2;
    }
};



    class Solution {
public:
    int maxXorSubsequences(vector<int> &nums) {
        vector<int> basis;
        for (int x: nums) {
            for (int b: basis) {
                x = min(x, x ^ b);
            }
            if (x)
                basis.push_back(x);
        }

        int ans = 0;
        for (int b: basis) {
            ans = max(ans, ans ^ b);
        }
        return ans;
    }
};




class Solution {
public:
    int minArrivalsToDiscard(vector<int> &arrivals, int w, int m) {
        unordered_map<int, int> cnt;
        int l = 0;
        int n = arrivals.size();
        int ans = 0;
        vector<bool> kept(n, false);

        for (int r = 0; r < n; r++) {
            int x = arrivals[r];
            cnt[x]++;
            if (cnt[x] > m) {
                cnt[x]--;
                ans++;
                if (cnt[x] == 0) {
                    cnt.erase(x);
                }
            } else {
                kept[r] = true;
            }

            if (r - w + 1 >= 0 && kept[r - w + 1]) {
                int y = arrivals[r - w + 1];
                if (cnt.contains(y)) {
                    cnt[y]--;
                    if (cnt[y] == 0) {
                        cnt.erase(y);
                    }
                }
            }
        }

        return ans;
    }
};






class Solution {
public:
    int smallestAbsent(vector<int> &nums) {
        int s = accumulate(nums.begin(), nums.end(), 0);
        int n = nums.size();
        double ave = 1.0 * s / n;

        unordered_set<int> st;
        for (int x: nums)
            st.insert(x);

        int i = 1;
        while (1) {
            if (i > ave && !st.contains(i)) {
                return i;
            }
        }
    }
};
