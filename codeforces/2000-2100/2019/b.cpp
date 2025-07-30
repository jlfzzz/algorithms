#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, q;
    cin >> n >> q;

    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<ll> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i];
    }

    map<ll, ll> mp;

    for (int i = 0; i < n; i++) {
        // 计算点 i 被覆盖的次数
        // 作为左端点: (n-1-i) 条
        // 作为右端点: i 条
        // 被穿过: i * (n-1-i) 条
        ll point_coverage = (n - 1 - i) + i + (ll) i * (n - 1 - i);
        mp[point_coverage]++;

        // 计算相邻区间内的点被覆盖的次数
        if (i < n - 1) {
            ll diff = nums[i + 1] - nums[i] - 1;
            if (diff > 0) {
                // 区间 (nums[i], nums[i+1]) 内的点被 (i+1) * (n-1-i) 条线段覆盖
                ll interval_coverage = (ll) (i + 1) * (n - 1 - i);
                mp[interval_coverage] += diff;
            }
        }
    }

    for (int i = 0; i < q; i++) {
        cout << mp[queries[i]];
        if (i < q - 1)
            cout << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
