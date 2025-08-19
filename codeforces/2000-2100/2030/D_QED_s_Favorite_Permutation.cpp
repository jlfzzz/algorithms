#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1), b(n + 2, 0), c(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 计算差分数组
    for (int i = 1; i <= n; i++) {
        int l = i, r = a[i];
        if (l > r)
            swap(l, r);
        b[l]++;
        b[r]--;
    }

    // 差分数组转实际数组
    for (int i = 1; i <= n; i++) {
        b[i] += b[i - 1];
    }

    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        c[i + 1] = (s[i] == 'R');
    }

    // 计算初始阻塞数量
    int cnt = 0;
    auto upt = [&](int x) -> bool {
        if (x >= n || x < 1)
            return false;
        return b[x] && !c[x] && c[x + 1];
    };

    for (int i = 1; i < n; i++) {
        cnt += upt(i);
    }

    while (q--) {
        int x;
        cin >> x;
        cnt -= upt(x) + upt(x - 1);
        c[x] ^= 1; // 翻转
        cnt += upt(x) + upt(x - 1);
        cout << (cnt ? "NO" : "YES") << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
