#include <bits/stdc++.h>
#include <deque>
#include <unordered_set>
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

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    map<int, int> mp;
    for (int x: a) {
        mp[x]++;
    }
    cout << mp.size() << '\n';

    deque<int> dq;
    set<int> st;
    For(i, n) {
        int x = a[i];
        mp[x]--;

        if (st.contains(x)) {
            continue;
        }

        while (!dq.empty() and mp[dq.back()] > 0) {
            int m = dq.size();
            int top = dq.back();

            if (m & 1) { // 奇数长度
                if (x < top && (m == 1 || x > dq[m - 2] || mp[dq[m - 2]] == 0)) {
                    break;
                }
            } else { // 偶数长度
                if (x > top && (m == 1 || x < dq[m - 2] || mp[dq[m - 2]] == 0)) {
                    break;
                }
            }

            st.erase(top);
            dq.pop_back();
        }
        st.emplace(x);
        dq.push_back(x);
    }
    for (int x: dq) {
        cout << x << ' ';
    }
    cout << '\n';
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
