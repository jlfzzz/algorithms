#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fori(n) for (int i = 0; i < (n); ++i)
#define ford(n) for (int i = (n) - 1; i >= 0; --i)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> nums(n);
    fori(n) {
        int l;
        cin >> l;
        vector<int> t(l);
        for (int j = 0; j < l; j++) {
            cin >> t[j];
        }
        nums[i] = std::move(t);
    }

    // unordered_map<int, int> mex1;
    int mx_mex = 0;
    fori(n) {
        auto &v = nums[i];
        unordered_set<int> st;
        for (int x: v) {
            st.insert(x);
        }
        int mex = 0;
        while (st.contains(mex)) {
            ++mex;
        }
        // int first_mex = mex;
        // mx_mex = max(mx_mex, first_mex);
        mex++;
        while (st.contains(mex)) {
            ++mex;
        }
        mx_mex = max(mx_mex, mex);
        // if (!mex1.contains(first_mex) or mex > mex1[first_mex]) {
        //     mex1[first_mex] = mex;
        // }
    }

    ll ans = 1LL * min(m + 1, mx_mex + 1) * mx_mex;
    // fori(min(mx_mex, m) + 1) {
    //     if (mex1.contains(i)) {
    //         int t = i;
    //         while (mex1.contains(t)) {
    //             t = mex1[t];
    //         }
    //         ans += t;
    //     } else {
    //         ans += i;
    //     }
    // }
    if (m > mx_mex) {
        ans += 1LL* (mx_mex + 1 + m) * (m - mx_mex) / 2;
    }
    cout << ans << '\n';
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
