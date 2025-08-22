#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n;
signed main() {
    cin >> t;
    while (t--) {
        cin >> n;
        string s = "";
        int temp, f = 1;
        while (1) {
            if (f) {
                cout << "? " << string(s + "0") << endl; // endl自动刷新缓冲区 这也是它慢的原因
                cin >> temp;
                if (temp)
                    s += "0";
                else {
                    cout << "? " << string(s + "1") << endl;
                    cin >> temp;
                    if (temp)
                        s += "1";
                    else
                        f = 0;
                }
            }
            if (!f) {
                cout << "? " << string("0" + s) << endl;
                cin >> temp;
                if (temp)
                    s = "0" + s;
                else
                    s = "1" + s;
            }
            if (s.size() == n) {
                cout << "! " << s << endl;
                break;
            }
        }
    }
    return 0;
}
