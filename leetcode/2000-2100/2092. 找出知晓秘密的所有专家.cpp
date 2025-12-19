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
    vector<int> findAllPeople(int n, vector<vector<int>> &meetings, int firstPerson) {
        sort(meetings.begin(), meetings.end(), [](const auto &a, const auto &b) { return a[2] < b[2]; });

        vector<bool> vis(n, false);
        vis[0] = true;
        vis[firstPerson] = true;

        int m = meetings.size();
        int i = 0;

        while (i < m) {
            int j = i;
            int time = meetings[i][2];

            while (j < m && meetings[j][2] == time) {
                j++;
            }

            unordered_map<int, vector<int>> adj;
            unordered_set<int> st;

            for (int k = i; k < j; k++) {
                int u = meetings[k][0];
                int v = meetings[k][1];
                adj[u].push_back(v);
                adj[v].push_back(u);
                st.insert(u);
                st.insert(v);
            }

            queue<int> q;
            for (int p: st) {
                if (vis[p]) {
                    q.push(p);
                }
            }

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v: adj[u]) {
                    if (!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }

            i = j;
        }

        vector<int> ans;
        for (int k = 0; k < n; k++) {
            if (vis[k])
                ans.push_back(k);
        }
        return ans;
    }
};
