#include <bits/stdc++.h>
using namespace std;
long long a, m, n, s, t, x;
int main() {
    ios::sync_with_stdio(0);
    cin >> t;
    while (t--) {
        cin >> n >> x;
        m = s = 0;
        while (n--) {
            cin >> a;
            m = max(a, m);
            s += a;
        }
        cout << max(m, (long long) ceil(1.0 * s / x)) << '\n';
    }
    return 0;
}
