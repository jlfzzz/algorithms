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
    long long minimumCost(string s, string t, int flipCost, int swapCost, int crossCost) {
        ll cnt1 = 0;
        ll cnt2 = 0;

        F(i, 0, SZ(s) - 1) {
            if (s[i] != t[i]) {
                if (s[i] == '0')
                    cnt1++;
                else
                    cnt2++;
            }
        }

        ll ans = 0;
        ll c1 = min(cnt1, cnt2);
        ans += c1 * min(swapCost, 2 * flipCost);

        ll rem = abs(cnt1 - cnt2);
        ans += (rem / 2) * min(crossCost + swapCost, 2 * flipCost);

        if (rem % 2) {
            ans += flipCost;
        }

        return ans;
    }
};
