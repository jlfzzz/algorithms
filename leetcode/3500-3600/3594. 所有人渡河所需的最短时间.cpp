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
    double minTime(int n, int k, int m, vector<int> &time, vector<double> &mul) {
        struct I {
            double t;
            int mask, time, person;

            bool operator<(const I &other) const { return t > other.t; }
        };

        if (k == 1 && n != 1) {
            return -1;
        }

        vector dis(n + 1, vector(m, vector<double>(1 << n, 1e300)));

        dis[n][0][0] = 0;
        priority_queue<I> pq;
        pq.emplace(0, 0, 0, -1);

        while (!pq.empty()) {
            auto [t, mask, ts, person] = pq.top();
            pq.pop();

            if (mask == ((1 << n) - 1)) {
                return t;
            }

            int ttt = (person == -1) ? n : 0;
            if (t > dis[ttt][ts][mask]) {
                continue;
            }

            if (person == n) {
                for (int i = 0; i < n; i++) {
                    if (mask >> i & 1) {
                        double cost = (double) time[i] * mul[ts];
                        int nts = (ts + (int) floor(cost)) % m;
                        int nmask = mask ^ (1 << i);
                        int np = -1;

                        if (t + cost < dis[n][nts][nmask]) {
                            dis[n][nts][nmask] = t + cost;
                            pq.push({t + cost, nmask, nts, np});
                        }
                    }
                }
            } else {
                vi a;
                for (int i = 0; i < n; i++) {
                    if (!(mask >> i & 1)) {
                        a.pb(i);
                    }
                }

                int sz = a.size();
                for (int nmask = 1; nmask < (1 << sz); nmask++) {
                    if (popcount((unsigned) nmask) > k) {
                        continue;
                    }

                    int mx = 0;
                    int mask2 = 0;

                    for (int i = 0; i < sz; i++) {
                        if (nmask >> i & 1) {
                            int original_idx = a[i];
                            mx = max(mx, time[original_idx]);
                            mask2 |= (1 << original_idx);
                        }
                    }

                    double cost = (double) mx * mul[ts];
                    int nts = (ts + (int) floor(cost)) % m;
                    int nnmask = mask | mask2;
                    int np = n;

                    if (t + cost < dis[0][nts][nnmask]) {
                        dis[0][nts][nnmask] = t + cost;
                        pq.push({t + cost, nnmask, nts, np});
                    }
                }
            }
        }
        return -1;
    }
};
