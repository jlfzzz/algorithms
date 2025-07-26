#include "bits/stdc++.h"
using namespace std;
using ll = long long;

class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>> &conflictingPairs) {
        vector<vector<int>> groups(n + 1, vector<int>());
        for (auto &con : conflictingPairs) {
            int a = con[0];
            int b = con[1];
            if (a > b) {
                swap(a, b);
            }

            groups[a].push_back(b);
        }

        vector<int> closest_two({ n + 1, n + 1 });
        long long ans = 0;
        vector<long long> extra(n + 2);

        for (int i = n; i >= 1; i--) {
            if (groups[i].size() > 0) {
                closest_two.insert(closest_two.end(), groups[i].begin(), groups[i].end());
                ranges::sort(closest_two);
                closest_two.resize(2);
            }
            ans += closest_two[0] - i;
            extra[closest_two[0]] += closest_two[1] - closest_two[0];
        }

        return ans + ranges::max(extra);
    }
};