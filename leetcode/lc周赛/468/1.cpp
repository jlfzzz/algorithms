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
    long long maxTotalValue(vector<int> &nums, int k) {
        int n = nums.size();

        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }

        set<int> st;
        for (int x: nums) {
            st.insert(x);
        }

        vector<int> LR;
        for (int x: st) {
            LR.push_back(x);
        }

        int l = 0, r = LR.size() - 1;
        int ans = 0;

        while (k) {
            int L = LR[l];
            int R = LR[r];
            auto &v1 = mp[L];

            if (L == R) {
                break;
            }

            auto &v2 = mp[R];

            for (int i = 0; i < v1.size(); i++) {
                for (int j = 0; j < v2.size(); j++) {
                    int x = v1[i];
                    int y = v2[j];

                    int mn = min(x, y);
                    int mx = max(x, y);

                    int left = mn;
                    int right = n - mx - 1;
                    int have = left * right;
                    if (k >= have) {
                        ans += (R - L) * have;
                        k -= have;
                    } else {
                        ans += (R - L) * k;
                        return ans;
                    }
                }
            }

            L++;
            R--;
        }

        return ans;
    }
};





// class Solution {
// public:
//     int minSplitMerge(vector<int> &nums1, vector<int> &nums2) {
//         int n = nums2.size();

//         if (nums2 == nums1) {
//             return 0;
//         }

//         queue<vector<int>> q;
//         unordered_map<string, int> cost;

//         auto f = [&](const vector<int> &v) {
//             string s;
//             for (int x: v) {
//                 s += to_string(x) + ",";
//             }
//             return s;
//         };

//         q.push(nums1);
//         cost[f(nums1)] = 0;

//         while (!q.empty()) {
//             auto cur = q.front();
//             q.pop();
//             int d = cost[f(cur)];

//             if (cur == nums2) {
//                 cout << d << "\n";
//                 return 0;
//             }

//             for (int L = 0; L < n; L++) {
//                 for (int R = L; R < n; R++) {
//                     vector<int> temp(cur.begin() + L, cur.begin() + R + 1);
//                     vector<int> LR;
//                     LR.insert(LR.end(), cur.begin(), cur.begin() + L);
//                     LR.insert(LR.end(), cur.begin() + R + 1, cur.end());

//                     for (int pos = 0; pos <= LR.size(); pos++) {
//                         vector<int> nxt = LR;
//                         nxt.insert(nxt.begin() + pos, temp.begin(), temp.end());
//                         string s = f(nxt);
//                         if (!cost.count(s)) {
//                             cost[s] = d + 1;
//                             q.push(nxt);
//                         }
//                     }
//                 }
//             }
//         }
//     }
// };


//     class Solution {
// public:
//     int evenNumberBitwiseORs(vector<int> &nums) {
//         int ans = 0;
//         for (int x: nums) {
//             if (x % 2 == 0) {
//                 ans |= x;
//             }
//         }
//         return ans;
//     }
// };
