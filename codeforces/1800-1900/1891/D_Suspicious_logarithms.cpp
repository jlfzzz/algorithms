#include <bits/stdc++.h>
using namespace std;
__int128 mod = 1000000007;
__int128 solve(__int128 l, __int128 r, __int128 d) {
    __int128 cl, cr, lx, rx, cw, ans;
    lx = 1;
    rx = d - 1;
    cw = 0;
    ans = 0;
    while (lx <= r) {
        cl = max(l, lx);
        cr = min(r, rx);
        if (cl <= cr)
            ans = (ans + (cr - cl + 1) * cw) % mod;
        lx = lx * d;
        rx = rx * d + d - 1;
        cw++;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int T;
    long long x, y;
    __int128 l, r, cl, cr, lx, rx, ans, i;
    for (cin >> T; T > 0; T--) {
        cin >> x >> y;
        l = x;
        r = y;
        lx = 4;
        rx = 7;
        ans = 0;
        for (i = 2; i <= 60; i++) {
            cl = max(l, lx);
            cr = min(r, rx);
            if (cl <= cr)
                ans = (ans + solve(cl, cr, i)) % mod;
            lx *= 2;
            rx = rx * 2 + 1;
        }
        cout << (long long) ans << '\n';
    }
    return 0;
}
