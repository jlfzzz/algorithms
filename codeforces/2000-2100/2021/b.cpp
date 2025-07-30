#include <bits/stdc++.h>
#include <functional>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n, y;
    cin >> n >> y;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int mex = 0;
    unordered_map<int, int> mp;
    for (int x: nums) {
        mp[x] += 1;
    }

    for (;; mex++) {
        if (!mp.contains(mex)) {
            break;
        }

        if (mp[mex] > 1) {
            mp[mex + y] += mp[mex] - 1;
        }
    }
    cout << mex << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
