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
    int maximumAND(vector<int> &a, int k, int m) {
        ll mx = ranges::max(a);
        int len = bit_width((unsigned) mx);
        ll ans = 0;
        vl cur;
        for (int x: a) {
            cur.pb(x);
        }

        D(i, 30, 0) {
            vl nxt, other;
            for (ll x: cur) {
                if (x >> i & 1) {
                    nxt.pb(x);
                } else {
                    other.pb(x);
                }
            }

            ll all1 = (1ll << i) - 1;
            ll u = 1ll << i;
            ranges::sort(other, [&](ll x, ll y) { return (u - (all1 & x)) < (u - (all1 & y)); });

            ll need = 0;
            ll have = SZ(nxt);
            F(j, 0, m - have - 1) { need += u - (all1 & other[j]); }

            if (need <= k) {
                k -= need;
                ans |= 1 << i;
                F(j, 0, m - have - 1) {
                    ll x = other[j];
                    x >>= i;
                    x <<= i;
                    x |= 1ll << i;
                    nxt.pb(x);
                }

                cur.swap(nxt);
            } else {
                continue;
            }
        }

        return ans;
    }
};
