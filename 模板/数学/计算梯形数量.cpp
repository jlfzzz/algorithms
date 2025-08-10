#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}


// 考虑了三点共线的情况

int countTrapezoids(vector<vector<int>> &points) {
    int n = points.size();

    unordered_map<int, unordered_map<int, unordered_map<int, vector<int>>>> mp;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int xa = points[i][0], ya = points[i][1];
            int xb = points[j][0], yb = points[j][1];
            int d2 = (xa - xb) * (xa - xb) + (ya - yb) * (ya - yb);
            int a = yb - ya, b = xa - xb, c = xb * ya - xa * yb;
            if (a < 0 || (a == 0 && b < 0) || (a == 0 && b == 0 && c < 0))
                a = -a, b = -b, c = -c;
            int g = gcd(gcd(abs(a), abs(b)), abs(c));
            a /= g;
            b /= g;
            c /= g;
            mp[a][b][c].push_back(d2);
        }

    int ans1 = 0, ans2 = 0;
    for (auto &pa: mp)
        for (auto &pb: pa.second) {
            int sm = 0;
            unordered_map<int, int> cnt;
            for (auto &pc: pb.second) {
                ans1 += pc.second.size() * sm;
                sm += pc.second.size();
                unordered_map<int, int> tmp;
                for (int d2: pc.second)
                    tmp[d2]++;
                for (auto &p: tmp) {
                    ans2 += p.second * cnt[p.first];
                    cnt[p.first] += p.second;
                }
            }
        }
    return ans1 - ans2 / 2;
}

void solve() {
    int N;
    cin >> N;
    vector<vector<int>> points(N, vector<int>(2));
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        points[i][0] = x;
        points[i][1] = y;
    }
    cout << countTrapezoids(points) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
