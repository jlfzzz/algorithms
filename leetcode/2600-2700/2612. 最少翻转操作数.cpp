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
    vector<int> minReverseOperations(int n, int p, vector<int> &banned, int k) {
        unordered_set<int> st(all(banned));
        vi dist(n, -1);
        dist[p] = 0;

        set<int> unvisited[2];
        F(i, 0, n - 1) {
            if (i != p && !st.count(i)) {
                unvisited[i % 2].ins(i);
            }
        }

        queue<int> q;
        q.push(p);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            int lmn = max(0, u - k + 1);
            int lmx = min(u, n - k);

            if (lmn > lmx)
                continue;


            int v_min = 2 * lmn + k - 1 - u;
            int v_max = 2 * lmx + k - 1 - u;

            int t = (v_min % 2 + 2) % 2;

            auto &st = unvisited[t];
            auto it = st.lower_bound(v_min);

            while (it != st.end() && *it <= v_max) {
                int v = *it;
                dist[v] = dist[u] + 1;
                q.push(v);

                it = st.erase(it);
            }
        }

        return dist;
    }
};
