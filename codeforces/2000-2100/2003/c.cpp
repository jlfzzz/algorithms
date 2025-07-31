#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    map<char, int> mp;
    for (char c: s) {
        mp[c] += 1;
    }

    string ans;
    while (!mp.empty()) {
        for (auto it = mp.begin(); it != mp.end();) {
            ans += it->first;
            if (--(it->second) == 0) {
                it = mp.erase(it); // 删除并返回下一个合法迭代器
            } else {
                ++it;
            }
        }
    }
    cout << ans << '\n';
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
