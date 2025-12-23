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
    bool is(char c) { return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; }

    long long beautifulSubstrings(string s, int k) {
        ll d = 1;
        while ((d * d) % k != 0) {
            d++;
        }

        map<pii, int> mp;
        mp[{0, 0}] = 1;

        ll v = 0, c = 0;
        ll ans = 0;
        int n = SZ(s);

        F(i, 0, n - 1) {
            if (is(s[i]))
                v++;
            else
                c++;

            ll diff = v - c;
            ll mod = v % d;

            if (mp.count({diff, mod})) {
                ans += mp[{diff, mod}];
            }

            mp[{diff, mod}]++;
        }

        return ans;
    }
};
