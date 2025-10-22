#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<LL> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (i >= k)
            a[i] += a[i - k];
    }
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;
        vector<LL> tmp(k);
        for (int i = 0, pos = r; i < k; ++i, pos--) {
            tmp[pos % k] = a[pos];
        }
        for (int i = 0, pos = l - 1; i < k && pos >= 0; ++i, pos--) {
            tmp[pos % k] -= a[pos];
        }
        cout << (set<LL>(tmp.begin(), tmp.end()).size() == 1 ? "Yes" : "No") << '\n';
    }



    return 0;
}
