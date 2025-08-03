#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int (i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);


#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);


class Solution {
public:
    int minTime(string s, vector<int> &order, int k) {
        int n = s.size();
        set<ll> added;
        added.insert(-1);
        added.insert(n);

        vector<ll> cnt(n + 1);

        for (int i = 0; i < n; i++) {
            ll pos = order[i];
            auto it = added.lower_bound(pos);
            ll right = *it;
            it--;
            ll left = *it;

            ll lenL = pos - left;
            ll lenR = right - pos;

            if (lenL >= INT_MAX / 2) {
                lenL = INT_MAX / 2;
            }
            if (lenR >= INT_MAX / 2) {
                lenR = INT_MAX / 2;
            }

            cnt[i + 1] = cnt[i] + lenL * lenR;
            added.insert(pos);
        }

        for (int i = 0; i <= n; i++) {
            if (cnt[i] >= k)
                return i - 1;
        }
        return -1;
    }
};
