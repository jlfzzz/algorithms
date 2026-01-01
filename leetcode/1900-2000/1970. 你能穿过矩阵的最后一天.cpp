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
    int latestDayToCross(int row, int col, vector<vector<int>> &cells) {
        vvi time(row, vi(col, inf));
        F(i, 0, SZ(cells) - 1) { time[cells[i][0] - 1][cells[i][1] - 1] = i + 1; }

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        auto check = [&](int day) -> bool {
            vvi vis(row, vi(col, 0));
            queue<pii> q;

            F(j, 0, col - 1) {
                if (time[0][j] > day) {
                    vis[0][j] = 1;
                    q.push({0, j});
                }
            }

            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();

                if (r == row - 1)
                    return true;

                F(i, 0, 3) {
                    int nr = r + dx[i];
                    int nc = c + dy[i];

                    if (nr >= 0 && nr < row && nc >= 0 && nc < col) {
                        if (!vis[nr][nc] && time[nr][nc] > day) {
                            vis[nr][nc] = 1;
                            q.push({nr, nc});
                        }
                    }
                }
            }
            return false;
        };

        int l = 0, r = SZ(cells);
        int ans = 0;

        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};
