#include <bits/stdc++.h>
using namespace std;

int calculate(vector<int> s, int first) {
    int n = s.size();
    int target = first;
    int operations = 0;

    for (int i = 0; i < n - 1; i++) {
        if (s[i] != target) {
            s[i] ^= 1; 
            s[i + 1] ^= 1;
            operations++;
        }
        target ^= 1; 
    }

    target = first;
    for (int i = 0; i < n; i++) {
        if (s[i] != target) {
            return 1e9;
        }
        target ^= 1;
    }

    return operations;
}

void solve() {
    int n;
    cin >> n;
    string str;
    cin >> str;

    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        s[i] = str[i] - '0';
    }

    int result = min(calculate(s, 0), calculate(s, 1));

    cout << (result >= 1e9 ? -1 : result) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
