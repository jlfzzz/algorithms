#include <bits/stdc++.h>

using namespace std;

const int N = 6e6;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<int> p, ip(N, 1);
    for (int i = 2; i < N; ++i) {
        if (!ip[i])
            continue;
        p.push_back(i);
        for (int j = i; j < N; j += i) {
            ip[j] = 0;
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &x: a)
            cin >> x;
        sort(a.begin(), a.end(), greater<int>());
        int ans = 0;
        long long suma = 0, sump = 0;
        for (int i = 0; i < n; ++i) {
            suma += a[i];
            sump += p[i];
            if (suma >= sump)
                ans = i + 1;
        }
        cout << n - ans << endl;
    }
}
