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
    int minOperations(string s, int k) {
        int n = SZ(s);
        int c0 = count(all(s), '0');

        if (c0 == 0)
            return 0;

        set<int> vis[2];
        F(i, 0, n) {
            if (i != c0)
                vis[i % 2].ins(i);
        }

        queue<int> q;
        q.push(c0);

        vi dist(n + 1, -1);
        dist[c0] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            int mx = min(k, u);
            int mn = max(0, k - (n - u));

            int v_min = u + k - 2 * mx;
            int v_max = u + k - 2 * mn;

            int parity = (u + k) % 2;

            auto &st = vis[parity];
            auto it = st.lower_bound(v_min);

            while (it != st.end() && *it <= v_max) {
                int v = *it;
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    if (v == 0)
                        return dist[v];
                    q.push(v);
                }
                it = st.erase(it);
            }
        }

        return -1;
    }
};

class Solution2 {
public:
    int minOperations(string s, int k) {
        int n = s.size();
        int cnt0 = count(s.begin(), s.end(), '0');

        vector<int> dis(n + 1, -1);
        deque<int> dq;
        dq.push_back(cnt0);
        dis[cnt0] = 0;
        set<int> even, odd;
        for (int i = 0; i <= n; i++) {
            if (i & 1) {
                odd.insert(i);
            } else {
                even.insert(i);
            }
        }
        if (cnt0 & 1)
            odd.erase(cnt0);
        else
            even.erase(cnt0);

        while (!dq.empty()) {
            int c0 = dq.front();
            dq.pop_front();

            int L1 = max(0, k - c0);
            int R1 = min(k, n - c0);

            if ((c0 + k) & 1) {
                auto it = odd.lower_bound(c0 + 2 * L1 - k);
                while (it != odd.end()) {
                    if (*it > c0 + 2 * R1 - k) {
                        break;
                    }
                    dis[*it] = dis[c0] + 1;
                    dq.push_back(*it);
                    odd.erase(it++);
                }
            } else {
                auto it = even.lower_bound(c0 + 2 * L1 - k);
                while (it != even.end()) {
                    if (*it > c0 + 2 * R1 - k) {
                        break;
                    }
                    dis[*it] = dis[c0] + 1;
                    dq.push_back(*it);
                    even.erase(it++);
                }
            }
        }
        return dis[0];
    }
};
