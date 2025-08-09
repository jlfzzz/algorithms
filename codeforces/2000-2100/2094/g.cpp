#include <bits/stdc++.h>
#include <deque>
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

void solve() {
    int q;
    cin >> q;
    vector<int> ans(q);
    int total_sum = 0;
    int rizziness = 0;
    deque<int> dq;
    bool dir = true;

    For(i, q) {
        int s;
        cin >> s;
        if (s == 1) {
            int t;
            if (dir) {
                t = dq.back();
                dq.pop_back();
                dq.push_front(t);
            } else {
                t = dq.front();
                dq.pop_front();
                dq.push_back(t);
            }
            rizziness = rizziness - dq.size() * t + total_sum;
        } else if (s == 2) {
            dir = !dir;
            rizziness = (dq.size() + 1) * total_sum - rizziness;
        } else {
            int k;
            cin >> k;

            total_sum += k;
            if (dir) {
                dq.push_back(k);
            } else {
                dq.push_front(k);
            }
            rizziness += dq.size() * k;
        }
        ans[i] = rizziness;
    }
    for (int x: ans) {
        cout << x << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
