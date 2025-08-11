#include <bits/stdc++.h>
using namespace std;
int a[200010];
int main() {
    int t, n, k;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        if (n == k) {
            int b = 1;
            for (int i = 2;; i += 2, ++b) {
                if (a[i] != b) {
                    cout << b << "\n";
                    break;
                }
            }
        } else {
            bool b = 0;
            for (int i = 2; i <= n - k + 2; ++i) {
                if (a[i] != 1) {
                    b = 1;
                    cout << 1 << "\n";
                    break;
                }
            }
            if (b == 0) {
                cout << 2 << "\n";
            }
        }
    }
}
