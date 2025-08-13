#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#define int long long
using namespace std;
int T;
int n;
const int N = 2e5 + 5;
int a[N];
vector<int> e;
signed main() {
    //    freopen(".in","r",stdin);
    //    freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--) {
        e.clear();
        map<int, int> vis;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i], vis[a[i]]++;
            if (vis[a[i]] == 2) {
                e.push_back(a[i]);
                vis[a[i]] = 0;
            }
        }
        if (e.size() < 4) {
            cout << "No" << '\n';
            continue;
        }
        sort(e.begin(), e.end());
        int len = e.size();
        cout << "Yes" << '\n';
        cout << e[len - 1] << ' ' << e[len - 2] << ' ' << e[len - 1] << ' ' << e[0] << ' ';
        cout << e[1] << ' ' << e[len - 2] << ' ' << e[1] << ' ' << e[0] << '\n';
    }
    return 0;
}
