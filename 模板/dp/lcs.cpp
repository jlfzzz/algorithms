#include "bits/stdc++.h"
using namespace std;


// 遍历一个数组,另一个数组存对应下标倒序构建新数组,再跑nlogn的lis
int calc1() {
    int n = 10;
    int m = 20;
    vector<int> s(n), t(m);

    map<int, vector<int>> cnt;
    for (int i = 0; i < m;i ++) {
        int cur = t[i];
        cnt[cur].push_back(i);
    }

    vector<int> v;
    for (int i = 0; i < n; i++) {
        int cur = s[i];
        if (!cnt.contains(cur)) {
            continue;
        }

        for (int j = cnt[cur].size() - 1; j >= 0; j--) {
            v.push_back(cnt[cur][j]);
        }
    }

    vector<int> dp;
    for (int x : v) {
        auto it = ranges::lower_bound(dp, x);
        if (it == dp.end()) {
            dp.push_back(x);
        } else {
            *it = x;
        }
    }

    int ans = dp.size();

    return ans;
}