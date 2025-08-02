#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int l = 2, r = 1000;
    while (l < r) {
        int L_mid = l + (r - l) / 3;
        int R_mid = r - (r - l) / 3;
        cout << "? " << L_mid << " " << R_mid << endl;
        int ans;
        cin >> ans;
        if (ans == L_mid * R_mid) {
            l = R_mid + 1;
        } else if (ans == (L_mid + 1) * (R_mid + 1)) {
            r = L_mid;
        } else {
            l = L_mid + 1;
            r = R_mid;
        }
    }
    cout << "! " << l << endl;
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
